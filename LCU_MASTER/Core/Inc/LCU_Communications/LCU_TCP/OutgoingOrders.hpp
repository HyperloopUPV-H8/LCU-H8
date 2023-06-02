#pragma once
#include "LCU_MASTER.hpp"
#include "Packets/Order.hpp"

namespace LCU{
	template<MASTER_MODE> class OutgoingOrders;

	template<> class OutgoingOrders<VEHICLE_5DOF>{
	public:
		HeapOrder start_slave_levitation_order;
		HeapOrder stop_slave_levitation_order;
		HeapOrder slave_hardware_reset_order;

		OutgoingOrders() : start_slave_levitation_order(405), stop_slave_levitation_order(406), slave_hardware_reset_order(407){

		}
	};
}
