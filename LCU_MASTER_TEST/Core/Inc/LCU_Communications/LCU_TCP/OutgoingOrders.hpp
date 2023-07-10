#pragma once
#include "LCU_MASTER.hpp"
#include "Packets/Order.hpp"

enum class SlaveOrdersID : uint16_t{
	START_SLAVE_LEVITATION = 405,
	STOP_SLAVE_LEVITATION = 406,
	SLAVE_HARDWARE_RESET = 407,
	SLAVE_TEST_ALL_PWM = 408,
	SLAVE_TEST_LPU = 409,
	SLAVE_TEST_CURRENT_CONTROL = 410,
	SLAVE_CHANGE_REFERENCE_CURERNT = 411,
	SLAVE_TEST_ALL_CURRENT_CONTROL = 412,
	SLAVE_TOGGLE_LED = 414,
	SLAVE_STOP_LPU = 415,
	STATE_SPACE = 7
};

namespace LCU{
	template<MASTER_MODE> class OutgoingOrders;

	template<> class OutgoingOrders<VEHICLE_5DOF>{
	public:
		COIL_ID coil_id;
		float duty_cycle;
		float reference_current;
	public:
		HeapOrder start_slave_levitation_order;
		HeapOrder stop_slave_levitation_order;
		HeapOrder slave_hardware_reset_order;
		HeapOrder test_toggle_led_order;
		HeapOrder state_space_order;
		HeapOrder test_slave_current_control_order;

		OutgoingOrders(Control<VEHICLE_5DOF>& control) : start_slave_levitation_order((uint16_t)SlaveOrdersID::START_SLAVE_LEVITATION),
				stop_slave_levitation_order((uint16_t)SlaveOrdersID::STOP_SLAVE_LEVITATION),
				slave_hardware_reset_order((uint16_t)SlaveOrdersID::SLAVE_HARDWARE_RESET),
				test_toggle_led_order((uint16_t)SlaveOrdersID::SLAVE_TOGGLE_LED),
				state_space_order((uint16_t)SlaveOrdersID::STATE_SPACE, &control.position_control.K[0],
						&control.position_control.K[1],
						&control.position_control.K[2],
						&control.position_control.K[3],
						&control.position_control.K[4],
						&control.position_control.K[5],
						&control.position_control.K[6],
						&control.position_control.K[7]),
				test_slave_current_control_order((uint16_t)SlaveOrdersID::SLAVE_TEST_CURRENT_CONTROL, &coil_id, &reference_current)
		{}
	};

	template<> class OutgoingOrders<VEHICLE_TESTING>{
	public:
		COIL_ID coil_id;
		float duty_cycle;
		float reference_current;
	public:
		HeapOrder slave_hardware_reset_order;
		HeapOrder test_all_slave_pwm_order;
		HeapOrder test_slave_lpu_order;
		HeapOrder test_slave_current_control_order;
		HeapOrder change_slave_current_control_reference_order;
		HeapOrder test_all_current_control_order;
		HeapOrder stop_slave_control_order;
		HeapOrder test_toggle_led_order;
		HeapOrder stop_lpu_order;

		OutgoingOrders() : slave_hardware_reset_order((uint16_t)SlaveOrdersID::SLAVE_HARDWARE_RESET),
				test_all_slave_pwm_order((uint16_t)SlaveOrdersID::SLAVE_TEST_ALL_PWM),
				test_slave_lpu_order((uint16_t)SlaveOrdersID::SLAVE_TEST_LPU, &coil_id, &duty_cycle),
				test_slave_current_control_order((uint16_t)SlaveOrdersID::SLAVE_TEST_CURRENT_CONTROL, &coil_id, &reference_current),
				change_slave_current_control_reference_order((uint16_t)SlaveOrdersID::SLAVE_CHANGE_REFERENCE_CURERNT, &reference_current),
				test_all_current_control_order((uint16_t)SlaveOrdersID::SLAVE_TEST_ALL_CURRENT_CONTROL, &reference_current),
				stop_slave_control_order((uint16_t)SlaveOrdersID::STOP_SLAVE_LEVITATION),
				test_toggle_led_order((uint16_t)SlaveOrdersID::SLAVE_TOGGLE_LED),
				stop_lpu_order((uint16_t)SlaveOrdersID::SLAVE_STOP_LPU)
				{}
	};
}