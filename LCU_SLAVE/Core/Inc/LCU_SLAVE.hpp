#pragma once
#include "LCU_Actuators/LCU_Actuators.hpp"
#include "LCU_Communications/LCU_TCP/LCU_TCP.hpp"
#include "LCU_Communications/LCU_UDP/LCU_UDP.hpp"
#include "LCU_Control/LCU_Control.hpp"
#include "LCU_Data/LCU_Data.hpp"
#include "LCU_StateMachine/LCU_StateMachine.hpp"
#include "LCU_Sensors/LCU_Sensors.hpp"

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

		static LCU_SLAVE& lcu_slave;

		LCU_SLAVE(): actuators(), data(), sensors(data), control(actuators,data), tcp_handler(), udp_handler(),
				state_machine_handler(data, actuators, control, tcp_handler){

		}


		static void read_currents(){
			lcu_slave.sensors.read_currents();
		}

		static void read_airgaps(){
			lcu_slave.sensors.read_airgaps();
		}
//		static void read_temperatures(){
//			lcu_master.sensors.read_temperatures();
//		}

		void init(){
			STLIB::start();
			actuators.init();
			state_machine_handler.init();
		}

	};

	LCU_SLAVE lcu;
	LCU_SLAVE& LCU_SLAVE::lcu_slave = lcu;
}
