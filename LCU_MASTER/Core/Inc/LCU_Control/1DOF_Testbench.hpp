#pragma once
#include "DistanceControl.hpp"

template<>
class DistanceControl<LCU::MASTER_MODE::LPU_VALIDATION>{
};

template<>
class DistanceControl<LCU::MASTER_MODE::TESTBENCH_1DOF>{
public:
	PID<IntegratorType::Trapezoidal,FilterDerivatorType::Moving_Average,22> pid = {ki,kp,kp,period};
	Saturator<float> target_current_saturator = Saturator((float)0.0,(float)-50.0,(float)50.0);
	static const float reference_distance = 0.0199;
	float target_current = 0.0;
	static const float ki = -7000, kp = -1400, kd = -475, period = 0.001;
	DistanceControl() = default;
	void set_reference_distance(float new_distance){
		reference_distance = new_distance;
	}
	void control(float real_distance){
		pid.input(reference_distance - real_distance/1000.0);
		pid.execute();
		target_current_saturator.input(pid.output_value);
		target_current_saturator.execute();
		target_current = target_current_saturator.output_value;
	}
};
