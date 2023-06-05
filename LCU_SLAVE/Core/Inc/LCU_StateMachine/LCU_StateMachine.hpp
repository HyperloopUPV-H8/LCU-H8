#pragma once
#include "StateMachine/StateMachine.hpp"
#include "Protections/ProtectionManager.hpp"
#include "BoardID/BoardID.hpp"
#include "LCU_Communications/LCU_TCP/LCU_TCP.hpp"
#include "LCU_Actuators/LCU_Actuators.hpp"
#include "Control/Blocks/MovingAverage.hpp"
#include "LCU_Control/LCU_Control.hpp"

using namespace std::chrono_literals;

namespace LCU{
	class SpecificStateMachine{
	public:
		StateMachine specific_state_machine;
		TimedAction* current_control_action;

		MovingAverage<40> z_error_filter;
		MovingAverage<40> z_position_filter;

		Control& control;

		enum SpecificStates{
			IDLE,
			LEVITATING
		};

		SpecificStateMachine(Control& control) : control(control){}

		void init(){
			specific_state_machine = {IDLE};
			specific_state_machine.add_state(LEVITATING);
			add_on_exit_actions();
			add_cyclic_actions();
		}

		void add_on_exit_actions(){
			specific_state_machine.add_exit_action([&](){
				control.stop();
				control.reset();
			}, LEVITATING);
		}

		void add_cyclic_actions(){
			specific_state_machine.add_mid_precision_cyclic_action([&](){
				control.execute_current_control();
			}, 500us, LEVITATING);
		}
	};
}

namespace LCU{
	class GeneralStateMachine{
	public:
		Actuators& actuators;
		Control& control;
		TCP& tcp_handler;
		StateMachine general_state_machine;
		SpecificStateMachine specific_state_machine_handler;
		bool tcp_timeout = false;

		static constexpr uint16_t max_tcp_connection_timeout = 5000; //ms

		enum States{
			INITIAL,
			OPERATIONAL,
			FAULT
		};

		GeneralStateMachine(Data& data, Actuators& actuators, Control& control, TCP& tcp_handler) : actuators(actuators),
				control(control), tcp_handler(tcp_handler), specific_state_machine_handler(control)
		{}

		void init(){
			general_state_machine = {INITIAL};
			general_state_machine.add_state(OPERATIONAL);
			general_state_machine.add_state(FAULT);
			ProtectionManager::link_state_machine(general_state_machine, FAULT);
			ProtectionManager::set_id(Boards::ID::LCU_SLAVE);
			add_on_enter_actions();
			add_on_exit_actions();
			add_transitions();
			register_timed_actions();
			add_transitions();
			general_state_machine.add_state_machine(specific_state_machine_handler.specific_state_machine, OPERATIONAL);
			specific_state_machine_handler.init();
		}

		void add_transitions(){
			general_state_machine.add_transition(INITIAL, OPERATIONAL, [&](){
				return tcp_handler.MASTER_CONNECTION.state == ServerSocket::ServerState::ACCEPTED;
			});
			general_state_machine.add_transition(INITIAL, FAULT, [&](){
				if(tcp_timeout) ErrorHandler("TCP connections could not be established in time and timed out");
				return tcp_timeout;
			});
			general_state_machine.add_transition(OPERATIONAL, FAULT, [&](){
				if(tcp_handler.MASTER_CONNECTION.state != ServerSocket::ServerState::ACCEPTED){
					ErrorHandler("TCP connections fell");
					return true;
				}
				return false;
			});
		}

		void add_on_enter_actions(){
			general_state_machine.add_enter_action([&](){
				Time::set_timeout(max_tcp_connection_timeout, [&](){
					if(not (tcp_handler.MASTER_CONNECTION.state == ServerSocket::ServerState::ACCEPTED)){
								tcp_timeout = true;
					}
				});
			}, INITIAL);

			Time::set_timeout(max_tcp_connection_timeout, [&](){
				if(not (tcp_handler.MASTER_CONNECTION.state == ServerSocket::ServerState::ACCEPTED)){
							tcp_timeout = true;
				}
			});

			general_state_machine.add_enter_action([&](){
				 control.stop();
				 actuators.turn_off();
			     actuators.led_operational.turn_off();
				 actuators.led_fault.turn_on();
			}, FAULT);

			general_state_machine.add_enter_action([&](){
				actuators.led_operational.turn_on();
			}, OPERATIONAL);
		}

		void add_on_exit_actions(){
			general_state_machine.add_exit_action([&](){
				actuators.led_fault.turn_off();
			}, FAULT);
			general_state_machine.add_exit_action([&](){
				actuators.led_operational.turn_off();
			}, OPERATIONAL);
		}

		void register_timed_actions(){
			general_state_machine.add_low_precision_cyclic_action([&](){
				actuators.led_operational.toggle();
			}, 150ms);
			//general_state_machine.add_low_precision_cyclic_action(ProtectionManager::check_protections, 1ms, OPERATIONAL);
		}
	};
}


