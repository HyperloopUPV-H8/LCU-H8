#pragma once
#include "Time/Time.hpp"
#include "Protections/ProtectionManager.hpp"
#include "LCU_Mode/LCU_Mode.hpp"
#include "LCU_Sensors/LCU_Sensors.hpp"

namespace LCU{
	template<LCU::MASTER_MODE> class CyclicActions;

	template<MASTER_MODE::VEHICLE_5DOF> class CyclicActions{
		Sensors<VEHICLE_5DOF>& sensors;
		CyclicActions(Sensors<VEHICLE_5DOF>& sensors) : sensors(sensors){}

		void register_cyclic_actions(){
			Time::register_high_precision_alarm(100, );
		}
	};
}
