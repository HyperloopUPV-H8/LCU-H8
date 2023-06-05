#pragma once
#include "Packets/Order.hpp"
#include "LCU_SLAVE.hpp"
#include "LCU_Pinout/Pinout.hpp"
namespace LCU{

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
		SLAVE_STOP_LPU = 415
	};

	void hardware_reset(){
		HAL_NVIC_SystemReset();
	}
	void start_levitation();

	void stop_levitation();

	void test_all_pwm();

	void test_lpu();

	void test_current_control();

	void change_reference_current();

	void test_all_current_control();

	void test_toggle_led();

	void stop_lpu();

	class IncomingOrders{
	public:

		COIL_ID coil_target;
		float duty_cycle;
		float reference_current;

		StackOrder<0> hardware_reset_order;
		StackOrder<0> start_levitation_order;
		StackOrder<0> stop_levitation_order;
		StackOrder<0> test_all_pwm_order;
		StackOrder<5, COIL_ID, float> test_lpu_order;
		StackOrder<5, COIL_ID, float> test_current_control_order;
		StackOrder<4, float> change_current_reference_order;
		StackOrder<4, float> test_all_current_control_order;
		StackOrder<0> test_toggle_led_order;
		StackOrder<0> stop_lpu_order;

		IncomingOrders(): hardware_reset_order((uint16_t)SlaveOrdersID::SLAVE_HARDWARE_RESET, hardware_reset),
				start_levitation_order((uint16_t)SlaveOrdersID::START_SLAVE_LEVITATION, start_levitation),
				stop_levitation_order((uint16_t)SlaveOrdersID::STOP_SLAVE_LEVITATION, stop_levitation),
				test_all_pwm_order((uint16_t)SlaveOrdersID::SLAVE_TEST_ALL_PWM, test_all_pwm),
				test_lpu_order((uint16_t)SlaveOrdersID::SLAVE_TEST_LPU, test_lpu, &coil_target, &duty_cycle),
				test_current_control_order((uint16_t)SlaveOrdersID::SLAVE_TEST_CURRENT_CONTROL, test_current_control,&coil_target, &reference_current),
				change_current_reference_order((uint16_t)SlaveOrdersID::SLAVE_CHANGE_REFERENCE_CURERNT, change_reference_current,&reference_current),
				test_all_current_control_order((uint16_t)SlaveOrdersID::SLAVE_TEST_ALL_CURRENT_CONTROL, test_all_current_control, &reference_current),
				test_toggle_led_order((uint16_t)SlaveOrdersID::SLAVE_TOGGLE_LED, test_toggle_led),
				stop_lpu_order((uint16_t)SlaveOrdersID::SLAVE_STOP_LPU, stop_lpu)
				{}
	};
}
