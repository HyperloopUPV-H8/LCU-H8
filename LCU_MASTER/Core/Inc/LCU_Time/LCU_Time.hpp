#pragma once
#include "LCU_MASTER.hpp"

namespace LCU{
	template<LCU::MASTER_MODE> class CyclicActions;

	template<> class CyclicActions<MASTER_MODE::LPU_VALIDATION>{
	public:
		CyclicActions(){}

		static void register_cyclic_actions(){
			Time::register_high_precision_alarm(100, LCU::LCU_MASTER<MASTER_MODE::LPU_VALIDATION>::read_currents);
			Time::register_high_precision_alarm(133, LCU::LCU_MASTER<MASTER_MODE::LPU_VALIDATION>::read_airgaps);
			Time::register_low_precision_alarm(100, LCU::LCU_MASTER<LPU_VALIDATION>::read_temperatures);
			Time::register_low_precision_alarm(16, LCU::LCU_MASTER<MASTER_MODE::LPU_VALIDATION>::send_vcu_data);
			Time::register_low_precision_alarm(1, LCU::LCU_MASTER<LPU_VALIDATION>::update_state_machine);
			Time::register_low_precision_alarm(50, LCU::LCU_MASTER<LPU_VALIDATION>::read_battery_voltages);
		}
	};

	template<> class CyclicActions<MASTER_MODE::VEHICLE_5DOF>{
	public:
		CyclicActions(){}

		static void register_cyclic_actions(){
			Time::register_high_precision_alarm(100, LCU::LCU_MASTER<MASTER_MODE::VEHICLE_5DOF>::read_currents);
			Time::register_high_precision_alarm(133, LCU::LCU_MASTER<MASTER_MODE::VEHICLE_5DOF>::read_airgaps);
			Time::register_low_precision_alarm(100, LCU::LCU_MASTER<VEHICLE_5DOF>::read_temperatures);
			Time::register_low_precision_alarm(16, LCU::LCU_MASTER<MASTER_MODE::VEHICLE_5DOF>::send_vcu_data);
			Time::register_low_precision_alarm(1, LCU::LCU_MASTER<VEHICLE_5DOF>::update_state_machine);
			Time::register_mid_precision_alarm(500, LCU::LCU_MASTER<MASTER_MODE::VEHICLE_5DOF>::send_slave_data);
		}
	};

	template<> class CyclicActions<MASTER_MODE::VEHICLE_TESTING>{
	public:
		CyclicActions(){}

		static void register_cyclic_actions(){
			Time::register_high_precision_alarm(100, LCU::LCU_MASTER<MASTER_MODE::VEHICLE_TESTING>::read_currents);
			Time::register_high_precision_alarm(133, LCU::LCU_MASTER<MASTER_MODE::VEHICLE_TESTING>::read_airgaps);
			Time::register_low_precision_alarm(100, LCU::LCU_MASTER<VEHICLE_TESTING>::read_temperatures);
			Time::register_low_precision_alarm(16, LCU::LCU_MASTER<MASTER_MODE::VEHICLE_TESTING>::send_vcu_data);
			Time::register_mid_precision_alarm(500, LCU::LCU_MASTER<MASTER_MODE::VEHICLE_TESTING>::send_slave_data);
			Time::register_low_precision_alarm(1, LCU::LCU_MASTER<VEHICLE_TESTING>::update_state_machine);
		}
	};
}
