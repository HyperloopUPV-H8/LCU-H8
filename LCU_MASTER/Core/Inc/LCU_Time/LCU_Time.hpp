#pragma once
#include "LCU_MASTER.hpp"

namespace LCU{
	template<LCU::MASTER_MODE> class CyclicActions;

	template<> class CyclicActions<MASTER_MODE::VEHICLE_5DOF>{
		Sensors<VEHICLE_5DOF>& sensors;
		CyclicActions(Sensors<VEHICLE_5DOF>& sensors) : sensors(sensors){}

		void register_cyclic_actions(){
			Time::register_high_precision_alarm(100, LCU::LCU_MASTER<MASTER_MODE::VEHICLE_5DOF>::read_currents);
			Time::register_high_precision_alarm(133, LCU::LCU_MASTER<MASTER_MODE::VEHICLE_5DOF>::read_airgaps);
		}
	};
}
