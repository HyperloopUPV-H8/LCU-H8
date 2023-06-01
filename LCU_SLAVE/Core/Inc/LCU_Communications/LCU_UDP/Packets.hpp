#pragma once
#include "../LCU_MASTER.hpp"

namespace LCU{
	template<MASTER_MODE> class Packets;

	template<>
	class Packets<VEHICLE_5DOF>{
	public:
		//TO VCU

		StackPacket<32,float,float,float,float,float,float,float,float> airgaps_data;

		StackPacket<32,float,float,float,float,float,float,float,float> coil_currents;

		StackPacket<32,float,float,float,float,float,float,float,float> coil_temperatures;

		StackPacket<32,float,float,float,float,float,float,float,float> lpu_temperatures;

		StackPacket<32,float,float,float,float,float,float,float,float> battery_data;

		StackPacket<>
	};
}