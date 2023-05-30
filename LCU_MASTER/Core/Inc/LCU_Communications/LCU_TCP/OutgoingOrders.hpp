#pragma once
#include "LCU_MASTER.hpp"

namespace LCU{
	template<MASTER_MODE> class OutgoingOrders;

	template<> class OutgoingOrders<VEHICLE_5DOF>{
	public:
		HeapOrder start_slave_levitation_order;
		HeapOrder stop_slave_levitation_order;

		OutgoingOrders() : start_slave_levitation_order(405), stop_slave_levitation_order(406){

		}
	};
}
