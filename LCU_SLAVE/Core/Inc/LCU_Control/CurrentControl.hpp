#pragma once
#include "Control/Blocks/PI.hpp"
#include "Control/Blocks/PID.hpp"
#include "Control/Blocks/Saturator.hpp"
#include "LCU_Actuators/LCU_Actuators.hpp"
#include "LCU_Actuators/LPU_HalfBridge.hpp"

class CurrentControl{
public:
	PI<IntegratorType::Trapezoidal> current_pi = PI<IntegratorType::Trapezoidal>(kp,ki,0.0005);
	Saturator<float> target_voltage_saturator = Saturator((float)0.0,min_voltage,max_voltage);
	Saturator<float> duty_saturator = Saturator((float)0.0,(float)-80.0,(float)80);
	LPU_HalfBridge half_bridge;
	float* reference_current = nullptr;
	float target_voltage = 0.0;
	static constexpr float battery_voltage = 100; //TODO:: update this in function to LPU voltage sensor
	static constexpr float kp = 5;
	static constexpr float ki = 50;
	static constexpr float max_voltage = battery_voltage, min_voltage = -battery_voltage;
	float target_duty_cyle = 0;

	CurrentControl();
	CurrentControl(LPU_HalfBridge& half_bridge, float& current_reference) : half_bridge(half_bridge), reference_current(&current_reference) {}

	void operator=(CurrentControl&& other){
		half_bridge = other.half_bridge;
		reference_current = other.reference_current;
	}

	void set_reference_current(float new_reference){
		*reference_current = new_reference;
	}

	void control(float real_current){
		current_pi.input(*reference_current - real_current);
		current_pi.execute();
		target_voltage_saturator.input(current_pi.output_value);
		target_voltage_saturator.execute();
		target_voltage = target_voltage_saturator.output_value;
		calculate_duty();
		apply_control();
	}
	void calculate_duty(){
		target_duty_cyle = (target_voltage/battery_voltage) * 100.0;
		duty_saturator.input(target_duty_cyle);
		duty_saturator.execute();
		target_duty_cyle = duty_saturator.output_value;
	}

	void apply_control(){
		half_bridge.set_duty_cycle(target_duty_cyle);
	}

	void reset(){
		current_pi.reset();
		target_duty_cyle = 0.0;
		target_voltage = 0.0;
	}

};