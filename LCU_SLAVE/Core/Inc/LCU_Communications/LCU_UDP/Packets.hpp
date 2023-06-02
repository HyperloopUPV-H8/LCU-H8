#pragma once
#include "LCU_SLAVE.hpp"
namespace LCU{
	class Packets{
	public:
		StackPacket<16,float,float,float,float> slave_reference_currents;

		StackPacket<16,float,float,float,float> slave_airgaps;

		Packets(Data& data): slave_reference_currents(309, &data.reference_currents[COIL_ID::HEMS_2], &data.reference_currents[COIL_ID::HEMS_4],&data.reference_currents[COIL_ID::EMS_2],&data.reference_currents[COIL_ID::EMS_4]),
			slave_airgaps(308, &data.airgaps[2-1], &data.airgaps[4-1],&data.airgaps[6-1],&data.airgaps[8-1]){}
	};
}
