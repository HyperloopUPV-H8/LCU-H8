#pragma once
#include "LCU_Actuators/LCU_Actuators.hpp"
#include "LCU_Communications/LCU_TCP/LCU_TCP.hpp"
#include "LCU_Communications/LCU_UDP/LCU_UDP.hpp"
#include "LCU_Control/LCU_Control.hpp"
#include "LCU_Data/LCU_Data.hpp"
#include "LCU_StateMachine/LCU_StateMachine.hpp"
#include "LCU_Sensors/LCU_Sensors.hpp"
#include "LCU_Time/LCU_Time.hpp"

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

		static LCU_MASTER<VEHICLE_5DOF>& lcu_master;

		LCU_MASTER(): actuators(), data(), sensors(data), control(actuators,data), tcp_handler(), udp_handler(),
				state_machine_handler(data, actuators, control, tcp_handler){

		}


		static void read_currents(){
			lcu_master.sensors.read_currents();
		}

		static void read_airgaps(){
			lcu_master.sensors.read_airgaps();
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

	LCU_MASTER<VEHICLE_5DOF> lcu;
	LCU_MASTER<VEHICLE_5DOF>& LCU_MASTER<VEHICLE_5DOF>::lcu_master = lcu;
}
