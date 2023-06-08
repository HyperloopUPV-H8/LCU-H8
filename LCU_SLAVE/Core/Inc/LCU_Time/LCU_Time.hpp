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
			Time::register_low_precision_alarm(100, LCU::LCU_SLAVE::read_temperatures);
			Time::register_mid_precision_alarm(500, LCU::LCU_SLAVE::send_airgaps_to_master);
			Time::register_low_precision_alarm(1, LCU::LCU_SLAVE::update_state_machine);
			Time::register_low_precision_alarm(10, LCU::LCU_SLAVE::send_coil_currents_to_master);
			Time::register_low_precision_alarm(100, LCU::LCU_SLAVE::send_coil_temperatures_to_master);
		}
	};
}
