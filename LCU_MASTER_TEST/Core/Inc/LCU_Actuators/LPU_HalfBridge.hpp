#pragma once

#include "PWM/PWM/PWM.hpp"

class LPU_HalfBridge{
public:
	PWM* H1, *H2;
	static float offset;
	LPU_HalfBridge() = default;
	LPU_HalfBridge(PWM* H1, PWM* H2) : H1(H1) , H2(H2){

	}

	void turn_on(){
		H1->turn_on();
		H2->turn_on();
	}

	void set_frequency(float frequency){
		H1->set_frequency(frequency);
		H2->set_frequency(frequency);
	}

	void set_duty_cycle(float duty){
		if(duty == 0){
			H1->set_duty_cycle(0);
			H2->set_duty_cycle(0);
			return;
		}
		if(duty > 0){
			H2->set_duty_cycle(0);
			H1->set_duty_cycle(duty + offset);
			return;
		}else{
			H1->set_duty_cycle(0);
			H2->set_duty_cycle(-duty + offset);
			return;
		}
	}

	void turn_off(){
		H1->set_duty_cycle(0);
		H2->set_duty_cycle(0);
	}
};


float LPU_HalfBridge::offset = 7;
