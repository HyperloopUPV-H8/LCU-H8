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
		StateMachine specific_state_machine;

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

		GeneralStateMachine(TCP<VEHICLE_5DOF>& tcp_handler,Data<VEHICLE_5DOF>& data, Actuators<VEHICLE_5DOF>& actuators, Control<VEHICLE_5DOF>& control) : tcp_handler(tcp_handler),
				actuators(actuators), control(control)
		{}

		void init(){
			general_state_machine = {INITIAL};
			general_state_machine.add_state(OPERATIONAL);
			general_state_machine.add_state(FAULT);
			ProtectionManager::link_state_machine(general_state_machine, FAULT);
			ProtectionManager::set_id(Boards::ID::LCU_MASTER);
			add_transitions();
			register_timed_actions();
			add_transitions();
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
			}, FAULT);
		}

		void register_timed_actions(){
			general_state_machine.add_low_precision_cyclic_action(ProtectionManager::check_protections, 1, OPERATIONAL);
		}
	};
}


