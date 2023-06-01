#pragma once
#include "LCU_MASTER.hpp"

namespace LCU{
	template<LCU::MASTER_MODE> class CyclicActions;

	template<> class CyclicActions<MASTER_MODE::VEHICLE_5DOF>{
	public:
		CyclicActions(){}

		static void register_cyclic_actions(){
			Time::register_high_precision_alarm(100, LCU::LCU_MASTER<MASTER_MODE::VEHICLE_5DOF>::read_currents);
			Time::register_high_precision_alarm(133, LCU::LCU_MASTER<MASTER_MODE::VEHICLE_5DOF>::read_airgaps);
			Time::register_low_precision_alarm(16, LCU::LCU_MASTER<MASTER_MODE::VEHICLE_5DOF>::send_vcu_data);
			Time::register_low_precision_alarm(1, LCU::LCU_MASTER<VEHICLE_5DOF>::update_state_machine);
			//Time::register_mid_precision_alarm(500, LCU::LCU_MASTER<MASTER_MODE::VEHICLE_5DOF>::send_slave_data);
		}
	};
}
