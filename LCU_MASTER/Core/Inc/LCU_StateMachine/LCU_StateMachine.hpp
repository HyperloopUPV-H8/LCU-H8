#pragma once
#include "LCU_Mode/LCU_Mode.hpp"
#include "StateMachine/StateMachine.hpp"
#include "Protections/ProtectionManager.hpp"
#include "BoardID/BoardID.hpp"
#include "LCU_Communications/LCU_TCP/LCU_TCP.hpp"
#include "LCU_Actuators/LCU_Actuators.hpp"
#include "LCU_Control/LCU_Control.hpp"

namespace LCU{
	template<LCU::MASTER_MODE> class SpecificStateMachine;

	template<> class SpecificStateMachine<LPU_VALIDATION>{

	};

	template<> class SpecificStateMachine<TESTBENCH_1DOF>{

	};

	template<> class SpecificStateMachine<VEHICLE_5DOF>{
	public:
		StateMachine specific_state_machine;

		static constexpr float ground = 0;        // TODO: ESTOS VALORES ME LOS HE INVENTADO SI SE VA A PROBAR A ATERRIZAR O DESPEGARSE CAMBIAR O BOOM BOOM
		static constexpr float ceiling = 0.7;

		static constexpr float accepted_error_percentage = 0.05; //Percentage of error that would consider levitation has achieved target reference

		TimedAction* distance_control_action;
		TimedAction* current_control_action;

		MovingAverage<40> z_error_filter;
		MovingAverage<40> z_position_filter;

		Control<VEHICLE_5DOF>& control;

		enum SpecificStates{
			IDLE,
			TAKING_OFF,
			STABLE,
			STICK_UP,
			STICK_DOWN,
			LANDING,
		};

		SpecificStateMachine(Control<VEHICLE_5DOF>& control) : control(control){}

		void init(){
			specific_state_machine = {IDLE};
			specific_state_machine.add_state(TAKING_OFF);
			specific_state_machine.add_state(STABLE);
			specific_state_machine.add_state(STICK_UP);
			specific_state_machine.add_state(STICK_DOWN);
			specific_state_machine.add_state(LANDING);
			add_transitions();
			add_on_exit_actions();
			add_cyclic_actions();
		}

		void add_transitions(){
			specific_state_machine.add_transition(TAKING_OFF, STABLE, [&](){
				return abs(z_error_filter.compute(control.position_control.error.z) / control.position_control.z_reference) < accepted_error_percentage;
			});
			specific_state_machine.add_transition(LANDING, IDLE, [&](){
				return abs(z_position_filter.compute(control.position_control.levitation_position.z)) < ground*(1+accepted_error_percentage);
			});
			specific_state_machine.add_transition(STICK_DOWN, IDLE, [&](){
				return abs(z_position_filter.compute(control.position_control.levitation_position.z)) < ground*(1+accepted_error_percentage);
			});
			specific_state_machine.add_transition(STICK_UP, IDLE, [&](){
				return abs(z_position_filter.compute(control.position_control.levitation_position.z)) > ceiling*(1-accepted_error_percentage);
			});
		}

		void add_on_exit_actions(){
			specific_state_machine.add_exit_action([&](){
				control.stop();
				control.reset();
			}, LANDING);

			specific_state_machine.add_exit_action([&](){
				control.stop();
				control.reset();
			}, STICK_DOWN);

			specific_state_machine.add_exit_action([&](){
				control.stop();
				control.reset();
			}, STICK_UP);
		}

		void add_cyclic_actions(){
			specific_state_machine.add_mid_precision_cyclic_action([&](){
				control.execute_current_control();
			}, 500, TAKING_OFF);
			specific_state_machine.add_mid_precision_cyclic_action([&](){
				control.execute_distance_control();
			}, 1000, TAKING_OFF);
			specific_state_machine.add_mid_precision_cyclic_action([&](){
				control.execute_current_control();
			}, 500, STABLE);
			specific_state_machine.add_mid_precision_cyclic_action([&](){
				control.execute_distance_control();
			}, 1000, STABLE);
			specific_state_machine.add_mid_precision_cyclic_action([&](){
				control.execute_current_control();
			}, 500, STICK_UP);
			specific_state_machine.add_mid_precision_cyclic_action([&](){
				control.execute_distance_control();
			}, 1000, STICK_UP);
			specific_state_machine.add_mid_precision_cyclic_action([&](){
				control.execute_current_control();
			}, 500, STICK_DOWN);
			specific_state_machine.add_mid_precision_cyclic_action([&](){
				control.execute_distance_control();
			}, 1000, STICK_DOWN);
			specific_state_machine.add_mid_precision_cyclic_action([&](){
				control.execute_current_control();
			}, 500, LANDING);
			specific_state_machine.add_mid_precision_cyclic_action([&](){
				control.execute_distance_control();
			}, 1000, LANDING);

			specific_state_machine.add_low_precision_cyclic_action([&](){
				control.set_z_reference(control.position_control.z_reference*0.99);
			}, 10, LANDING);

			specific_state_machine.add_low_precision_cyclic_action([&](){
				control.set_z_reference(control.position_control.z_reference*0.99);
			}, 1, STICK_DOWN);

			specific_state_machine.add_low_precision_cyclic_action([&](){
				control.set_z_reference(control.position_control.z_reference*1.01);
			}, 1, STICK_UP);
		}
	};
}

namespace LCU{
	template<LCU::MASTER_MODE> class GeneralStateMachine;

	template<> class GeneralStateMachine<LPU_VALIDATION>{

	};

	template<> class GeneralStateMachine<TESTBENCH_1DOF>{

	};

	template<> class GeneralStateMachine<VEHICLE_5DOF>{
		StateMachine general_state_machine;
		SpecificStateMachine<VEHICLE_5DOF> specific_state_machine_handler;
		TCP<VEHICLE_5DOF>& tcp_handler;
		Actuators<VEHICLE_5DOF>& actuators;
		Control<VEHICLE_5DOF>& control;
		bool tcp_timeout = false;

		static constexpr uint16_t max_tcp_connection_timeout = 5000; //ms

		enum States{
			INITIAL,
			OPERATIONAL,
			FAULT
		};

		GeneralStateMachine(Data<VEHICLE_5DOF>& data, Actuators<VEHICLE_5DOF>& actuators, Control<VEHICLE_5DOF>& control, TCP<VEHICLE_5DOF>& tcp_handler) : actuators(actuators),
				control(control), tcp_handler(tcp_handler), specific_state_machine_handler(control)
		{}

		void init(){
			general_state_machine = {INITIAL};
			general_state_machine.add_state(OPERATIONAL);
			general_state_machine.add_state(FAULT);
			ProtectionManager::link_state_machine(general_state_machine, FAULT);
			ProtectionManager::set_id(Boards::ID::LCU_MASTER);
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
				return tcp_handler.BACKEND_CONNECTION.state == ServerSocket::ServerState::ACCEPTED &&
					   tcp_handler.SLAVE_CONNECTION.state == Socket::SocketState::CONNECTED;
			});
			general_state_machine.add_transition(INITIAL, FAULT, [&](){
				if(tcp_timeout) ErrorHandler("TCP connections could not be established in time and timed out");
				return tcp_timeout;
			});
			general_state_machine.add_transition(OPERATIONAL, FAULT, [&](){
				if(tcp_handler.BACKEND_CONNECTION.state != ServerSocket::ServerState::ACCEPTED ||
						   tcp_handler.SLAVE_CONNECTION.state != Socket::SocketState::CONNECTED){
					ErrorHandler("TCP connections fell");
					return true;
				}
				return false;
			});
		}

		void add_on_enter_actions(){
			general_state_machine.add_enter_action([&](){
				Time::set_timeout(max_tcp_connection_timeout, [&](){
					if(not (tcp_handler.BACKEND_CONNECTION.state == ServerSocket::ServerState::ACCEPTED &&
						    tcp_handler.SLAVE_CONNECTION.state == Socket::SocketState::CONNECTED)){
								tcp_timeout = true;
					}
				});
			}, INITIAL);

			Time::set_timeout(max_tcp_connection_timeout, [&](){
				if(not (tcp_handler.BACKEND_CONNECTION.state == ServerSocket::ServerState::ACCEPTED &&
						tcp_handler.SLAVE_CONNECTION.state == Socket::SocketState::CONNECTED)){
							tcp_timeout = true;
				}
			});

			general_state_machine.add_enter_action([&](){
				 control.stop();
				 actuators.turn_off();
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
			general_state_machine.add_low_precision_cyclic_action(ProtectionManager::check_protections, 1, OPERATIONAL);
		}
	};
}

