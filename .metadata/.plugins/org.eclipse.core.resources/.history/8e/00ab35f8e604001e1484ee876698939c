#pragma once
#include "LCU_Pinout/Pinout.hpp"
#include "LCU_Mode/LCU_Mode.hpp"
#include "LPU_HalfBridge.hpp"
#include "DigitalOutput/DigitalOutput.hpp"
#include "PWM/PWM/PWM.hpp"


namespace LCU{
    template<LCU::MASTER_MODE> class Actuators;

    template<>
    class Actuators<LPU_VALIDATION> {
    public:
        static constexpr float default_pwm_frequency = 20000;
        LPU_HalfBridge HEMS_1, HEMS_3, EMS_1, EMS_3;
        DigitalOutput buffer_enable {Pinout::BUFFER_EN_PIN};
    	DigitalOutput led_sleep, led_flash, led_fault, led_operational, led_can;
        PWM HEMS1_H1 = {Pinout::HEMS1_H1_PIN}, HEMS1_H2 = {Pinout::HEMS1_H2_PIN}, HEMS3_H1 = {Pinout::HEMS3_H1_PIN}, HEMS3_H2 = {Pinout::HEMS3_H2_PIN}, EMS1_H1 = {Pinout::EMS1_H1_PIN}, EMS1_H2 = {Pinout::EMS1_H2_PIN}, EMS3_H1 = {Pinout::EMS3_H1_PIN}, EMS3_H2 = {Pinout::EMS3_H2_PIN};
        Actuators() : HEMS_1(&HEMS1_H1, &HEMS1_H2), HEMS_3(&HEMS3_H1, &HEMS3_H2), EMS_1(&EMS1_H1, &EMS1_H2), EMS_3(&EMS3_H1, &EMS3_H2), led_sleep(Pinout::SLEEP_LED_PIN), led_flash(Pinout::FLASH_LED_PIN), led_fault(Pinout::FAULT_LED_PIN),
				led_operational(Pinout::OPERATIONAL_LED_PIN), led_can(Pinout::CAN_LED_PIN) {}

        void init();
        void turn_off();
        void turn_on();

        void set_duty_cycle(COIL_ID id, float duty);

        void test_all_pwm();

        void change_all_pwm(float duty_cycle);

        void change_frequency(float frequency);
    };

    void Actuators<LPU_VALIDATION>::init(){
        HEMS_1.turn_on();
        HEMS_3.turn_on();
        EMS_1.turn_on();
        EMS_3.turn_on();
        HEMS_1.set_frequency(default_pwm_frequency);
        HEMS_3.set_frequency(default_pwm_frequency);
        EMS_1.set_frequency(default_pwm_frequency);
        EMS_3.set_frequency(default_pwm_frequency);
        HEMS_1.set_duty_cycle(0);
        HEMS_3.set_duty_cycle(0);
        EMS_1.set_duty_cycle(0);
        EMS_3.set_duty_cycle(0);
        buffer_enable.turn_off();
    }

    void Actuators<LPU_VALIDATION>::turn_off(){
    	buffer_enable.turn_on();
        HEMS_1.turn_off();
        HEMS_3.turn_off();
        EMS_1.turn_off();
        EMS_3.turn_off();
    }

    void Actuators<LPU_VALIDATION>::turn_on(){
        HEMS_1.set_duty_cycle(0);
        HEMS_3.set_duty_cycle(0);
        EMS_1.set_duty_cycle(0);
        EMS_3.set_duty_cycle(0);
        HEMS_1.turn_on();
        HEMS_3.turn_on();
        EMS_1.turn_on();
        EMS_3.turn_on();
        buffer_enable.turn_off();
    }

    void Actuators<LPU_VALIDATION>::set_duty_cycle(COIL_ID id, float duty){
        switch (id){
            case COIL_ID::HEMS_1:
                HEMS_1.set_duty_cycle(duty);
                break;
            case COIL_ID::HEMS_3:
                HEMS_3.set_duty_cycle(duty);
                break;
            case COIL_ID::EMS_1:
                EMS_1.set_duty_cycle(duty);
                break;
            case COIL_ID::EMS_3:
                EMS_3.set_duty_cycle(duty);
                break;
            default:
                ErrorHandler("Invalid HEMS_ID, given id: %d", id);
                break;
        }
    }

    void Actuators<LPU_VALIDATION>::test_all_pwm(){
        HEMS_1.H1->set_duty_cycle(50);
        HEMS_1.H2->set_duty_cycle(50);
        HEMS_3.H1->set_duty_cycle(50);
        HEMS_3.H2->set_duty_cycle(50);
        EMS_1.H1->set_duty_cycle(50);
        EMS_1.H2->set_duty_cycle(50);
        EMS_3.H1->set_duty_cycle(50);
        EMS_3.H2->set_duty_cycle(50);
    }

    void Actuators<LPU_VALIDATION>::change_all_pwm(float duty_cycle){
        HEMS_1.H1->set_duty_cycle(duty_cycle);
        HEMS_1.H2->set_duty_cycle(duty_cycle);
        HEMS_3.H1->set_duty_cycle(duty_cycle);
        HEMS_3.H2->set_duty_cycle(duty_cycle);
        EMS_1.H1->set_duty_cycle(duty_cycle);
        EMS_1.H2->set_duty_cycle(duty_cycle);
        EMS_3.H1->set_duty_cycle(duty_cycle);
        EMS_3.H2->set_duty_cycle(duty_cycle);
    }

    void Actuators<LPU_VALIDATION>::change_frequency(float frequency){
        HEMS_1.set_frequency(frequency);
        HEMS_3.set_frequency(frequency);
        EMS_1.set_frequency(frequency);
        EMS_3.set_frequency(frequency);
    }

    template<>
    class Actuators<TESTBENCH_1DOF> {
    public:

        Actuators(COIL_ID id);


        LPU_HalfBridge HEMS;
        void init();
        void turn_off();
        void set_duty_cycle(float duty);
    private:
        static constexpr float pwm_frequency = 20000;
        COIL_ID hems_id;
        PWM HEMS_H1, HEMS_H2;
    };

    Actuators<TESTBENCH_1DOF>::Actuators(COIL_ID id){
        hems_id = id;
        switch(id){
            case COIL_ID::HEMS_1:
                HEMS_H1 = PWM(LCU::Pinout::HEMS1_H1_PIN);
                HEMS_H2 = PWM(LCU::Pinout::HEMS1_H2_PIN);
                HEMS = LPU_HalfBridge(&HEMS_H1, &HEMS_H2);
                break;
            case COIL_ID::HEMS_3:
                HEMS_H1 = PWM(LCU::Pinout::HEMS3_H1_PIN);
                HEMS_H2 = PWM(LCU::Pinout::HEMS3_H2_PIN);
                HEMS = LPU_HalfBridge(&HEMS_H1, &HEMS_H2);
                break;
            case COIL_ID::EMS_1:
                HEMS_H1 = PWM(LCU::Pinout::EMS1_H1_PIN);
                HEMS_H2 = PWM(LCU::Pinout::EMS1_H2_PIN);
                HEMS = LPU_HalfBridge(&HEMS_H1, &HEMS_H2);
                break;
            case COIL_ID::EMS_3:
                HEMS_H1 = PWM(LCU::Pinout::EMS3_H1_PIN);
                HEMS_H2 = PWM(LCU::Pinout::EMS3_H2_PIN);
                HEMS = LPU_HalfBridge(&HEMS_H1, &HEMS_H2);
                break;
        }
    }

    void Actuators<TESTBENCH_1DOF>::init(){
        HEMS_H1.turn_on();
        HEMS_H2.turn_on();
        HEMS_H1.set_duty_cycle(0);
        HEMS_H2.set_duty_cycle(0);
        HEMS_H1.set_frequency(pwm_frequency);
        HEMS_H2.set_frequency(pwm_frequency);
    }

    void Actuators<TESTBENCH_1DOF>::turn_off(){
        HEMS_H1.turn_off();
        HEMS_H2.turn_off();
    }

    void Actuators<TESTBENCH_1DOF>::set_duty_cycle(float duty){
        HEMS_H1.set_duty_cycle(duty);
        HEMS_H2.set_duty_cycle(duty);
    }

    template<>
    class Actuators<VEHICLE_5DOF>{
    public:
    	LPU_HalfBridge HEMS_1, HEMS_3, EMS_1, EMS_3;
    	DigitalOutput led_sleep, led_flash, led_fault, led_operational, led_can;
    	void init();
    	void turn_off();
    	void turn_on();
    	void toggle_led();
    private:
        static constexpr float default_pwm_frequency = 20000;
        DigitalOutput buffer_enable {Pinout::BUFFER_EN_PIN};
        PWM HEMS1_H1 = {Pinout::HEMS1_H1_PIN}, HEMS1_H2 = {Pinout::HEMS1_H2_PIN}, HEMS3_H1 = {Pinout::HEMS3_H1_PIN}, HEMS3_H2 = {Pinout::HEMS3_H2_PIN}, EMS1_H1 = {Pinout::EMS1_H1_PIN}, EMS1_H2 = {Pinout::EMS1_H2_PIN}, EMS3_H1 = {Pinout::EMS3_H1_PIN}, EMS3_H2 = {Pinout::EMS3_H2_PIN};
    public:
        Actuators() : HEMS_1(&HEMS1_H1, &HEMS1_H2), HEMS_3(&HEMS3_H1, &HEMS3_H2), EMS_1(&EMS1_H1, &EMS1_H2), EMS_3(&EMS3_H1, &EMS3_H2),
				led_sleep(Pinout::SLEEP_LED_PIN), led_flash(Pinout::FLASH_LED_PIN), led_fault(Pinout::FAULT_LED_PIN),
				led_operational(Pinout::OPERATIONAL_LED_PIN), led_can(Pinout::CAN_LED_PIN)
        		{}
    };

    void Actuators<VEHICLE_5DOF>::init(){
        HEMS_1.turn_on();
        HEMS_3.turn_on();
        EMS_1.turn_on();
        EMS_3.turn_on();
        HEMS_1.set_frequency(default_pwm_frequency);
        HEMS_3.set_frequency(default_pwm_frequency);
        EMS_1.set_frequency(default_pwm_frequency);
        EMS_3.set_frequency(default_pwm_frequency);
        HEMS_1.set_duty_cycle(0);
        HEMS_3.set_duty_cycle(0);
        EMS_1.set_duty_cycle(0);
        EMS_3.set_duty_cycle(0);
        buffer_enable.turn_off();
    }
    void Actuators<VEHICLE_5DOF>::turn_off(){
    	buffer_enable.turn_on();
        HEMS_1.turn_off();
        HEMS_3.turn_off();
        EMS_1.turn_off();
        EMS_3.turn_off();
    }

    void Actuators<VEHICLE_5DOF>::turn_on(){
        HEMS_1.set_duty_cycle(0);
        HEMS_3.set_duty_cycle(0);
        EMS_1.set_duty_cycle(0);
        EMS_3.set_duty_cycle(0);
        HEMS_1.turn_on();
        HEMS_3.turn_on();
        EMS_1.turn_on();
        EMS_3.turn_on();
        buffer_enable.turn_off();
    }

    void Actuators<VEHICLE_5DOF>::toggle_led(){
    	led_can.toggle();
    }

    template<>
    class Actuators<VEHICLE_TESTING>{
    public:
    	LPU_HalfBridge HEMS_1, HEMS_3, EMS_1, EMS_3;
    	DigitalOutput led_sleep, led_flash, led_fault, led_operational, led_can;
    	void init();
    	void turn_off();
    	void turn_on();
    	void toggle_led();
        void set_duty_cycle(COIL_ID id, float duty);
        void change_frequency(COIL_ID, float frequency);
        void test_all_pwm();
        static bool is_coil_from_master(COIL_ID id);
    private:
        static constexpr float default_pwm_frequency = 20000;
        DigitalOutput buffer_enable {Pinout::BUFFER_EN_PIN};
        PWM HEMS1_H1 = {Pinout::HEMS1_H1_PIN}, HEMS1_H2 = {Pinout::HEMS1_H2_PIN}, HEMS3_H1 = {Pinout::HEMS3_H1_PIN}, HEMS3_H2 = {Pinout::HEMS3_H2_PIN}, EMS1_H1 = {Pinout::EMS1_H1_PIN}, EMS1_H2 = {Pinout::EMS1_H2_PIN}, EMS3_H1 = {Pinout::EMS3_H1_PIN}, EMS3_H2 = {Pinout::EMS3_H2_PIN};
    public:
        Actuators() : HEMS_1(&HEMS1_H1, &HEMS1_H2), HEMS_3(&HEMS3_H1, &HEMS3_H2), EMS_1(&EMS1_H1, &EMS1_H2), EMS_3(&EMS3_H1, &EMS3_H2),
				led_sleep(Pinout::SLEEP_LED_PIN), led_flash(Pinout::FLASH_LED_PIN), led_fault(Pinout::FAULT_LED_PIN),
				led_operational(Pinout::OPERATIONAL_LED_PIN), led_can(Pinout::CAN_LED_PIN)
        		{}
    };

    void Actuators<VEHICLE_TESTING>::init(){
        HEMS_1.turn_on();
        HEMS_3.turn_on();
        EMS_1.turn_on();
        EMS_3.turn_on();
        HEMS_1.set_frequency(default_pwm_frequency);
        HEMS_3.set_frequency(default_pwm_frequency);
        EMS_1.set_frequency(default_pwm_frequency);
        EMS_3.set_frequency(default_pwm_frequency);
        HEMS_1.set_duty_cycle(0);
        HEMS_3.set_duty_cycle(0);
        EMS_1.set_duty_cycle(0);
        EMS_3.set_duty_cycle(0);
        buffer_enable.turn_off();
    }

    void Actuators<VEHICLE_TESTING>::turn_off(){
    	buffer_enable.turn_on();
        HEMS_1.turn_off();
        HEMS_3.turn_off();
        EMS_1.turn_off();
        EMS_3.turn_off();
    }

    void Actuators<VEHICLE_TESTING>::turn_on(){
        HEMS_1.set_duty_cycle(0);
        HEMS_3.set_duty_cycle(0);
        EMS_1.set_duty_cycle(0);
        EMS_3.set_duty_cycle(0);
        HEMS_1.turn_on();
        HEMS_3.turn_on();
        EMS_1.turn_on();
        EMS_3.turn_on();
        buffer_enable.turn_off();
    }

    void Actuators<VEHICLE_TESTING>::toggle_led(){
    	led_can.toggle();
    }

    void Actuators<VEHICLE_TESTING>::set_duty_cycle(COIL_ID id, float duty){
        switch (id){
            case COIL_ID::HEMS_1:
                HEMS_1.set_duty_cycle(duty);
                break;
            case COIL_ID::HEMS_3:
                HEMS_3.set_duty_cycle(duty);
                break;
            case COIL_ID::EMS_1:
                EMS_1.set_duty_cycle(duty);
                break;
            case COIL_ID::EMS_3:
                EMS_3.set_duty_cycle(duty);
                break;
            default:
                ErrorHandler("Invalid COIL_ID, given id: %d", id);
                break;
        }
    }

    bool Actuators<VEHICLE_TESTING>::is_coil_from_master(COIL_ID id){
    	if(id == COIL_ID::HEMS_1 || id == COIL_ID::HEMS_3 || id == COIL_ID::EMS_1 || id == COIL_ID::EMS_3) return true;
    	return false;
    }

    void Actuators<VEHICLE_TESTING>::change_frequency(COIL_ID id, float frequency){
        switch (id){
            case COIL_ID::HEMS_1:
                HEMS_1.set_frequency(frequency);
                break;
            case COIL_ID::HEMS_3:
                HEMS_3.set_frequency(frequency);
                break;
            case COIL_ID::EMS_1:
                EMS_1.set_frequency(frequency);
                break;
            case COIL_ID::EMS_3:
                EMS_3.set_frequency(frequency);
                break;
            default:
                ErrorHandler("Invalid COIL_ID, given id: %d", id);
                break;
        }
    }

    void Actuators<VEHICLE_TESTING>::test_all_pwm(){
		HEMS_1.H1->set_duty_cycle(50);
		HEMS_1.H2->set_duty_cycle(50);
		HEMS_3.H1->set_duty_cycle(50);
		HEMS_3.H2->set_duty_cycle(50);
		EMS_1.H1->set_duty_cycle(50);
		EMS_1.H2->set_duty_cycle(50);
		EMS_3.H1->set_duty_cycle(50);
		EMS_3.H2->set_duty_cycle(50);
    }

}

