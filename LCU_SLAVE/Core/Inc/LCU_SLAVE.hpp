#pragma once
#include "LCU_Actuators/LCU_Actuators.hpp"
#include "LCU_Communications/LCU_TCP/LCU_TCP.hpp"
#include "LCU_Communications/LCU_UDP/LCU_UDP.hpp"
#include "LCU_Control/LCU_Control.hpp"
#include "LCU_Data/LCU_Data.hpp"
#include "LCU_StateMachine/LCU_StateMachine.hpp"
#include "LCU_Sensors/LCU_Sensors.hpp"
#include "LCU_Communications/LCU_UDP/Packets.hpp"
#include "LCU_Communications/LCU_TCP/IncomingOrders.hpp"
#include "LCU_Communications/LCU_TCP/OutgoingOrders.hpp"

namespace LCU{
	class LCU_SLAVE{
	public:
		Actuators actuators;
		Data data;
		Sensors sensors;
		Control control;
		TCP tcp_handler;
		UDP udp_handler;
		GeneralStateMachine state_machine_handler;
		Packets packets;
		IncomingOrders incoming_orders;

		static LCU_SLAVE* lcu_slave;

		LCU_SLAVE(): actuators(), data(), sensors(data), control(actuators,data), tcp_handler(), udp_handler(),
				state_machine_handler(data, actuators, control, tcp_handler), packets(data){

		}


		static void read_currents(){
			lcu_slave->sensors.read_currents();
		}

		static void toggle_led(){
			lcu_slave->actuators.led_can.toggle();
		}

		static void read_airgaps(){
			lcu_slave->sensors.read_airgaps();
		}
//		static void read_temperatures(){
//			lcu_master.sensors.read_temperatures();
//		}

		static void send_to_master(){
			lcu_slave->udp_handler.send_to_master(lcu_slave->packets.slave_airgaps);
		}

		static void update_state_machine(){
			lcu_slave->state_machine_handler.general_state_machine.check_transitions();
		}

		void init(){
			STLIB::start();
			udp_handler.init();
			tcp_handler.init();
			actuators.init();
			state_machine_handler.init();
		}

	};

	void test_toggle_led(){
		LCU_SLAVE::toggle_led();
		Time::set_timeout(500, LCU_SLAVE::toggle_led);
	}

	void start_levitation(){
		LCU_SLAVE::toggle_led();
		if(LCU_SLAVE::lcu_slave->state_machine_handler.general_state_machine.current_state == GeneralStateMachine::OPERATIONAL &&
				LCU_SLAVE::lcu_slave->state_machine_handler.specific_state_machine_handler.specific_state_machine.current_state == SpecificStateMachine::IDLE){
			LCU_SLAVE::lcu_slave->state_machine_handler.specific_state_machine_handler.specific_state_machine.force_change_state(SpecificStateMachine::LEVITATING);
		}
		Time::set_timeout(500, LCU_SLAVE::toggle_led);
	}

	void stop_levitation(){
		LCU_SLAVE::toggle_led();
		LCU_SLAVE::lcu_slave->state_machine_handler.specific_state_machine_handler.specific_state_machine.force_change_state(SpecificStateMachine::IDLE);
		LCU_SLAVE::lcu_slave->control.stop();
		LCU_SLAVE::lcu_slave->actuators.turn_off();
		LCU_SLAVE::lcu_slave->actuators.turn_on();
		LCU_SLAVE::lcu_slave->control.reset();
		Time::set_timeout(500, LCU_SLAVE::toggle_led);
	}

	LCU_SLAVE* LCU_SLAVE::lcu_slave = nullptr;
}
