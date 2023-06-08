#pragma once
#include "LCU_SLAVE.hpp"
namespace LCU{
	class Packets{
	public:
		StackPacket<16,float,float,float,float> slave_reference_currents;

		StackPacket<16,float,float,float,float> slave_airgaps;

		StackPacket<16,float,float,float,float> slave_coil_currents;

		StackPacket<16,float,float,float,float> slave_coil_temperatures;

		Packets(Data& data): slave_reference_currents(309, &data.reference_currents[COIL_ID::HEMS_2], &data.reference_currents[COIL_ID::HEMS_4],&data.reference_currents[COIL_ID::EMS_2],&data.reference_currents[COIL_ID::EMS_4]),
			slave_airgaps(408, &data.airgaps[2-1], &data.airgaps[4-1],&data.airgaps[6-1],&data.airgaps[8-1]),
			slave_coil_currents(410, &data.coil_current_hems_2, &data.coil_current_hems_4, &data.coil_current_ems_2, &data.coil_current_ems_4),
			slave_coil_temperatures(411, &data.hems_2_temperature, &data.hems_4_temperature, &data.ems_2_temperature, &data.ems_4_temperature){}
	};
}
