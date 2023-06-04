#pragma once
#include "LCU_Pinout/Pinout.hpp"
#include "LPU_HalfBridge.hpp"
#include "DigitalOutput/DigitalOutput.hpp"
#include "PWM/PWM/PWM.hpp"


namespace LCU{
	class Actuators{
	public:
    	LPU_HalfBridge HEMS_2, HEMS_4, EMS_2, EMS_4;
    	DigitalOutput led_sleep, led_flash, led_fault, led_operational, led_can;
    	void init();
    	void turn_off();
    	void turn_on();
    	void test_all_pwm();
    	void set_duty_cycle(COIL_ID id, float duty_cycle);
    	void set_frequency(COIL_ID id, float frequency);
    	static bool is_coil_from_slave(COIL_ID id);
    private:
        static constexpr float default_pwm_frequency = 20000;
        DigitalOutput buffer_enable {Pinout::BUFFER_EN_PIN};
        PWM HEMS2_H1 = {Pinout::HEMS2_H1_PIN}, HEMS2_H2 = {Pinout::HEMS2_H2_PIN}, HEMS4_H1 = {Pinout::HEMS4_H1_PIN}, HEMS4_H2 = {Pinout::HEMS4_H2_PIN}, EMS2_H1 = {Pinout::EMS2_H1_PIN}, EMS2_H2 = {Pinout::EMS2_H2_PIN}, EMS4_H1 = {Pinout::EMS4_H1_PIN}, EMS4_H2 = {Pinout::EMS4_H2_PIN};
    public:
        Actuators() : HEMS_2(&HEMS2_H1, &HEMS2_H2), HEMS_4(&HEMS4_H1, &HEMS4_H2), EMS_2(&EMS2_H1, &EMS2_H2), EMS_4(&EMS4_H1, &EMS4_H2),
				led_sleep(Pinout::SLEEP_LED_PIN), led_flash(Pinout::FLASH_LED_PIN), led_fault(Pinout::FAULT_LED_PIN),
				led_operational(Pinout::OPERATIONAL_LED_PIN), led_can(Pinout::CAN_LED_PIN)
        		{}
	};

    void Actuators::init(){
        HEMS_2.turn_on();
        HEMS_4.turn_on();
        EMS_2.turn_on();
        EMS_4.turn_on();
        HEMS_2.set_frequency(default_pwm_frequency);
        HEMS_4.set_frequency(default_pwm_frequency);
        EMS_2.set_frequency(default_pwm_frequency);
        EMS_4.set_frequency(default_pwm_frequency);
        HEMS_2.set_duty_cycle(0);
        HEMS_4.set_duty_cycle(0);
        EMS_2.set_duty_cycle(0);
        EMS_4.set_duty_cycle(0);
        buffer_enable.turn_off();
    }
    void Actuators::turn_off(){
    	buffer_enable.turn_on();
        HEMS_2.turn_off();
        HEMS_4.turn_off();
        EMS_2.turn_off();
        EMS_4.turn_off();
    }

    void Actuators::turn_on(){
        HEMS_2.set_duty_cycle(0);
        HEMS_4.set_duty_cycle(0);
        EMS_2.set_duty_cycle(0);
        EMS_4.set_duty_cycle(0);
        HEMS_2.turn_on();
        HEMS_4.turn_on();
        EMS_2.turn_on();
        EMS_4.turn_on();
        buffer_enable.turn_off();
    }

    void Actuators::test_all_pwm(){
		HEMS_2.H1->set_duty_cycle(50);
		HEMS_2.H2->set_duty_cycle(50);
		HEMS_4.H1->set_duty_cycle(50);
		HEMS_4.H2->set_duty_cycle(50);
		EMS_2.H1->set_duty_cycle(50);
		EMS_2.H2->set_duty_cycle(50);
		EMS_4.H1->set_duty_cycle(50);
		EMS_4.H2->set_duty_cycle(50);
    }

    void Actuators::set_duty_cycle(COIL_ID id, float duty){
        switch (id){
            case COIL_ID::HEMS_2:
                HEMS_2.set_duty_cycle(duty);
                break;
            case COIL_ID::HEMS_4:
                HEMS_4.set_duty_cycle(duty);
                break;
            case COIL_ID::EMS_2:
                EMS_2.set_duty_cycle(duty);
                break;
            case COIL_ID::EMS_4:
                EMS_4.set_duty_cycle(duty);
                break;
            default:
                ErrorHandler("Invalid COIL_ID, given id: %d", id);
                break;
        }
    }

    void Actuators::set_frequency(COIL_ID id, float frequency){
        switch (id){
            case COIL_ID::HEMS_2:
                HEMS_2.set_frequency(frequency);
                break;
            case COIL_ID::HEMS_4:
                HEMS_4.set_frequency(frequency);
                break;
            case COIL_ID::EMS_2:
                EMS_2.set_frequency(frequency);
                break;
            case COIL_ID::EMS_4:
                EMS_4.set_frequency(frequency);
                break;
            default:
                ErrorHandler("Invalid COIL_ID, given id: %d", id);
                break;
        }
    }

	bool Actuators::is_coil_from_slave(COIL_ID id){
    	if(id == COIL_ID::HEMS_2 || id == COIL_ID::HEMS_4 || id == COIL_ID::EMS_2 || id == COIL_ID::EMS_4) return true;
    	return false;
	}

}

