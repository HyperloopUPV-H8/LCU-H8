#pragma once
#include "Packets/Order.hpp"
#include "LCU_SLAVE.hpp"
namespace LCU{

	void hardware_reset(){
		HAL_NVIC_SystemReset();
	}
	void start_levitation();

	void stop_levitation();

	class IncomingOrders{
	public:
		StackOrder<0> hardware_reset_order;
		StackOrder<0> start_levitation_order;
		StackOrder<0> stop_levitation_order;

		IncomingOrders(): hardware_reset_order(407, hardware_reset), start_levitation_order(405, start_levitation), stop_levitation_order(406, stop_levitation){}
	};
}
