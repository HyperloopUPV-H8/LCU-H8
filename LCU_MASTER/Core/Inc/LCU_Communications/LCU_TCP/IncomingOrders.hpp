#pragma once
#include "LCU_Data/LCU_Data.hpp"

namespace LCU{

	void test_toggle_led();

	void start_levitating();

	void start_landing();

	void start_stick_up();

	void start_stick_down();

	void stop_levitation();

	void hardware_reset(){
		HAL_NVIC_SystemReset();
	}

	template<MASTER_MODE> class IncomingOrders;

	template<> class IncomingOrders<VEHICLE_5DOF>{
	public:
		Data<VEHICLE_5DOF>& data;

		StackOrder<0> test_toggle_led_order;
		StackOrder<0> start_levitating_order;
		StackOrder<0> landing_order;
		StackOrder<0> stick_up_order;
		StackOrder<0> stick_down_order;
		StackOrder<0> stop_levitation_order;
		StackOrder<0> hardware_reset_order;

		IncomingOrders(Data<VEHICLE_5DOF>& data) : data(data),
				test_toggle_led_order(318,test_toggle_led),
				start_levitating_order(315, start_levitating),
				landing_order(301, start_landing),
				stick_up_order(303, start_stick_up),
				stick_down_order(303, start_stick_down),
				stop_levitation_order(316, stop_levitation),
				hardware_reset_order(317, hardware_reset)
				{
		}

		void init(){}
	};
}
