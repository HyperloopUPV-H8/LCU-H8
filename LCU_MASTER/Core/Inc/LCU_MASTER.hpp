#pragma once

#include "LCU_Actuators/LCU_Actuators.hpp"
#include "LCU_Communications/LCU_TCP/LCU_TCP.hpp"
#include "LCU_Communications/LCU_UDP/LCU_UDP.hpp"
#include "LCU_Control/LCU_Control.hpp"
#include "LCU_Data/LCU_Data.hpp"
#include "LCU_StateMachine/LCU_StateMachine.hpp"
#include "LCU_Sensors/LCU_Sensors.hpp"
#include "LCU_Communications/LCU_TCP/IncomingOrders.hpp"
#include "LCU_Communications/LCU_TCP/OutgoingOrders.hpp"
#include "LCU_Communications/LCU_UDP/Packets.hpp"

namespace LCU{
	template<LCU::MASTER_MODE> class LCU_MASTER;


	template<>
	class LCU_MASTER<VEHICLE_5DOF>{
	public:
		Actuators<VEHICLE_5DOF> actuators;
		Data<VEHICLE_5DOF> data;
		Sensors<VEHICLE_5DOF> sensors;
		Control<VEHICLE_5DOF> control;
		TCP<VEHICLE_5DOF> tcp_handler;
		UDP<VEHICLE_5DOF> udp_handler;
		GeneralStateMachine<VEHICLE_5DOF> state_machine_handler;
		IncomingOrders<VEHICLE_5DOF> incoming_orders_handler;
		OutgoingOrders<VEHICLE_5DOF> outgoing_orders_handler;
		Packets<VEHICLE_5DOF> packets;

		static LCU_MASTER<VEHICLE_5DOF>* lcu_master;

		LCU_MASTER(): actuators(), data(), sensors(data), control(actuators,data), tcp_handler(), udp_handler(),
				state_machine_handler(data, actuators, control, tcp_handler, outgoing_orders_handler), incoming_orders_handler(data), packets(data){
		}

		static void read_currents(){
			lcu_master->sensors.read_currents();
		}

		static void read_airgaps(){
			lcu_master->sensors.read_airgaps();
		}

		static void toggle_led(){
			lcu_master->actuators.led_can.toggle();
		}

		static void send_vcu_data(){
			lcu_master->udp_handler.send_to_backend(lcu_master->packets.airgaps_data);
			lcu_master->udp_handler.send_to_backend(lcu_master->packets.coil_currents);
		}

		static void send_slave_data(){
			lcu_master->udp_handler.send_to_slave(lcu_master->packets.slave_airgaps);
			lcu_master->udp_handler.send_to_slave(lcu_master->packets.slave_reference_currents);
		}

		static void update_state_machine(){
			lcu_master->state_machine_handler.general_state_machine.check_transitions();
		}

//		static void read_temperatures(){
//			lcu_master->sensors.read_temperatures();
//		}

		void init(){
			STLIB::start();
			udp_handler.init();
			tcp_handler.init();
			actuators.init();
			state_machine_handler.init();
		}

	};

	LCU_MASTER<VEHICLE_5DOF>* LCU_MASTER<VEHICLE_5DOF>::lcu_master = nullptr;

	void test_toggle_led(){
		LCU_MASTER<VEHICLE_5DOF>::toggle_led();
		Time::set_timeout(500, LCU_MASTER<VEHICLE_5DOF>::toggle_led);
	}

	void start_levitating(){
		LCU_MASTER<VEHICLE_5DOF>::toggle_led();
		if(LCU_MASTER<VEHICLE_5DOF>::lcu_master->state_machine_handler.general_state_machine.current_state == GeneralStateMachine<VEHICLE_5DOF>::OPERATIONAL &&
				LCU_MASTER<VEHICLE_5DOF>::lcu_master->state_machine_handler.specific_state_machine_handler.specific_state_machine.current_state == SpecificStateMachine<VEHICLE_5DOF>::IDLE){
			LCU_MASTER<VEHICLE_5DOF>::lcu_master->state_machine_handler.specific_state_machine_handler.specific_state_machine.force_change_state(SpecificStateMachine<VEHICLE_5DOF>::TAKING_OFF);
		}
		Time::set_timeout(500, LCU_MASTER<VEHICLE_5DOF>::toggle_led);
	}

	void stop_levitation(){
		LCU_MASTER<VEHICLE_5DOF>::toggle_led();
		LCU_MASTER<VEHICLE_5DOF>::lcu_master->state_machine_handler.specific_state_machine_handler.specific_state_machine.force_change_state(SpecificStateMachine<VEHICLE_5DOF>::IDLE);
		LCU_MASTER<VEHICLE_5DOF>::lcu_master->control.stop();
		LCU_MASTER<VEHICLE_5DOF>::lcu_master->actuators.turn_off();
		LCU_MASTER<VEHICLE_5DOF>::lcu_master->actuators.turn_on();
		LCU_MASTER<VEHICLE_5DOF>::lcu_master->control.reset();
		Time::set_timeout(500, LCU_MASTER<VEHICLE_5DOF>::toggle_led);
	}


	void start_landing(){

	}

	void start_stick_up(){

	}

	void start_stick_down(){

	}

}
