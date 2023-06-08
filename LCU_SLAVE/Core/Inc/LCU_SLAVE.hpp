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
		vector<TimedAction*> control_actions;

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

		static void read_temperatures(){
			lcu_slave->sensors.read_temps();
		}

		static void send_airgaps_to_master(){
			lcu_slave->udp_handler.send_to_master(lcu_slave->packets.slave_airgaps);
		}

		static void send_coil_currents_to_master(){
			lcu_slave->udp_handler.send_to_master(lcu_slave->packets.slave_coil_currents);
		}

		static void send_coil_temperatures_to_master(){
			lcu_slave->udp_handler.send_to_master(lcu_slave->packets.slave_coil_temperatures);
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
			data.add_protections();
			sensors.current_zeroing();
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
		for(TimedAction*& control_action : LCU_SLAVE::lcu_slave->control_actions){
			LCU_SLAVE::lcu_slave->state_machine_handler.general_state_machine.remove_cyclic_action(control_action);
		}
		LCU_SLAVE::lcu_slave->control_actions.clear();
		for(float& reference_current : LCU_SLAVE::lcu_slave->data.reference_currents) reference_current = 0.0;
		LCU_SLAVE::lcu_slave->control.reset();
		LCU_SLAVE::lcu_slave->actuators.turn_on();
		Time::set_timeout(500, LCU_SLAVE::toggle_led);
	}

	void test_all_pwm(){
		LCU_SLAVE::toggle_led();
		LCU_SLAVE::lcu_slave->actuators.test_all_pwm();
		Time::set_timeout(500, LCU_SLAVE::toggle_led);
	}

	void test_lpu(){
		LCU_SLAVE::toggle_led();
		COIL_ID target_coil = LCU_SLAVE::lcu_slave->incoming_orders.coil_target;
		float target_duty = LCU_SLAVE::lcu_slave->incoming_orders.duty_cycle;
		LCU_SLAVE::lcu_slave->actuators.set_duty_cycle(target_coil, target_duty);
		Time::set_timeout(500, LCU_SLAVE::toggle_led);
	}

	void test_current_control(){
		LCU_SLAVE::toggle_led();
		COIL_ID target_coil = LCU_SLAVE::lcu_slave->incoming_orders.coil_target;
		float reference_current = LCU_SLAVE::lcu_slave->incoming_orders.reference_current;
		LCU_SLAVE::lcu_slave->control.change_current_reference(target_coil, reference_current);
		TimedAction* control_action = LCU_SLAVE::lcu_slave->state_machine_handler.general_state_machine.add_mid_precision_cyclic_action([&, target_coil](){
			LCU_SLAVE::lcu_slave->control.execute_current_control(target_coil);
		}, 500us);
		LCU_SLAVE::lcu_slave->control_actions.push_back(control_action);
		Time::set_timeout(500, LCU_SLAVE::toggle_led);
	}

	void change_reference_current(){
		LCU_SLAVE::toggle_led();
		float reference_current = LCU_SLAVE::lcu_slave->incoming_orders.reference_current;
		for(COIL_ID id = HEMS_1; id <= EMS_4; id++){
			if(LCU_SLAVE::lcu_slave->data.reference_currents[id] != 0 && Actuators::is_coil_from_slave(id)){
				LCU_SLAVE::lcu_slave->control.change_current_reference(id, reference_current);
			}
		}
		Time::set_timeout(500, LCU_SLAVE::toggle_led);
	}

	void stop_lpu(){
		LCU_SLAVE::toggle_led();
		for(COIL_ID id = HEMS_1; id<=EMS_4; id++){
			if(Actuators::is_coil_from_slave(id)){
				LCU_SLAVE::lcu_slave->actuators.set_duty_cycle(id, 0);
			}
		}
		Time::set_timeout(500, LCU_SLAVE::toggle_led);
	}

	void test_all_current_control(){
		LCU_SLAVE::toggle_led();
		float reference_current = LCU_SLAVE::lcu_slave->incoming_orders.reference_current;
		for(COIL_ID id = HEMS_1; id <= EMS_4; id++){
			if(Actuators::is_coil_from_slave(id)){
				LCU_SLAVE::lcu_slave->control.change_current_reference(id, reference_current);
			}
		}
		TimedAction* control_action = LCU_SLAVE::lcu_slave->state_machine_handler.general_state_machine.add_mid_precision_cyclic_action([&](){
			LCU_SLAVE::lcu_slave->control.execute_current_control();
		}, 500us);
		LCU_SLAVE::lcu_slave->control_actions.push_back(control_action);
		Time::set_timeout(500, LCU_SLAVE::toggle_led);
	}

	LCU_SLAVE* LCU_SLAVE::lcu_slave = nullptr;
}
