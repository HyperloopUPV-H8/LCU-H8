#pragma once
#include "LCU_Pinout/Pinout.hpp"
#include "LCU_Mode/LCU_Mode.hpp"
#include "LPU_HalfBridge.hpp"
#include "PWM/PWM/PWM.hpp"


namespace LCU{
    template<LCU::MASTER_MODE> class Actuators;

    template<>
    class Actuators<LPU_VALIDATION> {
    public:
        static constexpr float default_pwm_frequency = 20000;
        LPU_HalfBridge HEMS1, HEMS3, EMS1, EMS3;
        DigitalOutput buffer_enable {Pinout::BUFFER_EN_PIN};
        PWM HEMS1_H1 = {Pinout::HEMS1_H1_PIN}, HEMS1_H2 = {Pinout::HEMS1_H2_PIN}, HEMS3_H1 = {Pinout::HEMS3_H1_PIN}, HEMS3_H2 = {Pinout::HEMS3_H2_PIN}, EMS1_H1 = {Pinout::EMS1_H1_PIN}, EMS1_H2 = {Pinout::EMS1_H2_PIN}, EMS3_H1 = {Pinout::EMS3_H1_PIN}, EMS3_H2 = {Pinout::EMS3_H2_PIN};
        Actuators() : HEMS1(&HEMS1_H1, &HEMS1_H2), HEMS3(&HEMS3_H1, &HEMS3_H2), EMS1(&EMS1_H1, &EMS1_H2), EMS3(&EMS3_H1, &EMS3_H2) {}

        void init(){
            HEMS1.turn_on();
            HEMS3.turn_on();
            EMS1.turn_on();
            EMS3.turn_on();
            HEMS1.set_frequency(default_pwm_frequency);
            HEMS3.set_frequency(default_pwm_frequency);
            EMS1.set_frequency(default_pwm_frequency);
            EMS3.set_frequency(default_pwm_frequency);
            HEMS1.set_duty_cycle(0);
            HEMS3.set_duty_cycle(0);
            EMS1.set_duty_cycle(0);
            EMS3.set_duty_cycle(0);
            buffer_enable.turn_off();
        }
        void turn_off(){
        	buffer_enable.turn_on();
            HEMS1.turn_off();
            HEMS3.turn_off();
            EMS1.turn_off();
            EMS3.turn_off();
        }

        void set_duty_cycle(COIL_ID id, float duty){
            switch (id){
                case COIL_ID::HEMS_1:
                    HEMS1.set_duty_cycle(duty);
                    break;
                case COIL_ID::HEMS_3:
                    HEMS3.set_duty_cycle(duty);
                    break;
                case COIL_ID::EMS_1:
                    EMS1.set_duty_cycle(duty);
                    break;
                case COIL_ID::EMS_3:
                    EMS3.set_duty_cycle(duty);
                    break;
                default:
                    ErrorHandler("Invalid HEMS_ID, given id: %d", id);
                    break;
            }
        }

        void test_all_pwm(){
            HEMS1.H1->set_duty_cycle(50);
            HEMS1.H2->set_duty_cycle(50);
            HEMS3.H1->set_duty_cycle(50);
            HEMS3.H2->set_duty_cycle(50);
            EMS1.H1->set_duty_cycle(50);
            EMS1.H2->set_duty_cycle(50);
            EMS3.H1->set_duty_cycle(50);
            EMS3.H2->set_duty_cycle(50);
        }

        void change_all_pwm(float duty_cycle){
            HEMS1.H1->set_duty_cycle(duty_cycle);
            HEMS1.H2->set_duty_cycle(duty_cycle);
            HEMS3.H1->set_duty_cycle(duty_cycle);
            HEMS3.H2->set_duty_cycle(duty_cycle);
            EMS1.H1->set_duty_cycle(duty_cycle);
            EMS1.H2->set_duty_cycle(duty_cycle);
            EMS3.H1->set_duty_cycle(duty_cycle);
            EMS3.H2->set_duty_cycle(duty_cycle);
        }

        void change_frequency(float frequency){
            HEMS1.set_frequency(frequency);
            HEMS3.set_frequency(frequency);
            EMS1.set_frequency(frequency);
            EMS3.set_frequency(frequency);
        }
    };

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
}

