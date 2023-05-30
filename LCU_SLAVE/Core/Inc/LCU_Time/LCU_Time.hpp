#pragma once
#include "LCU_SLAVE.hpp"

namespace LCU{
	class CyclicActions{
	public:
		Sensors& sensors;
		CyclicActions(Sensors& sensors) : sensors(sensors){}

		static void register_cyclic_actions(){
			Time::register_high_precision_alarm(100, LCU::LCU_SLAVE::read_currents);
			Time::register_high_precision_alarm(133, LCU::LCU_SLAVE::read_airgaps);
		}
	};
}
