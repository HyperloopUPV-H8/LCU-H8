#pragma once
#include "LCU_Actuators/LCU_Actuators.hpp"
#include "DistanceControl.hpp"
#include "1DOF_Testbench.hpp"
#include "1DOF_Vehicle.hpp"
#include "5DOF.hpp"
#include "LCU_Mode/LCU_Mode.hpp"
#include "CurrentControl.hpp"

namespace LCU {
    template<LCU::MASTER_MODE> class Control;

    template<> class Control<LCU::MASTER_MODE::LPU_VALIDATION>{
        public:
            CurrentControl current_control;
            Control(LCU::Actuators<LPU_VALIDATION>& actuators, HEMS_ID hems_id){
                switch (hems_id){
                    case HEMS_ID::HEMS_1:
                        current_control = {actuators.HEMS1};
                        break;
                    case HEMS_ID::HEMS_3:
                        current_control = {actuators.HEMS3};
                        break;
                    case HEMS_ID::EMS_1:
                        current_control = {actuators.EMS1};
                        break;
                    case HEMS_ID::EMS_3:
                        current_control = {actuators.EMS3};
                        break;
                    default:
                        ErrorHandler("Invalid HEMS_ID, given id: %d", hems_id);
                        break;
                }
                current_control.half_bridge.turn_on();
            }

            void execute(float real_current){
                current_control.control(real_current);
            }

            void set_reference(float reference){
                current_control.set_reference(reference);
            }

            void stop(){
                current_control.half_bridge.turn_off();
            }

            void reset(){
            	current_control.current_pi.reset();
            	current_control.half_bridge.turn_on();
            }
    }; 

    template<> class Control<LCU::MASTER_MODE::TESTBENCH_1DOF>{
    public:
    	CurrentControl current_control;
    	DistanceControl<TESTBENCH_1DOF> distance_control;
        Control(LCU::Actuators<LPU_VALIDATION>& actuators, HEMS_ID hems_id){
            switch (hems_id){
                case HEMS_ID::HEMS_1:
                    current_control = CurrentControl(actuators.HEMS1);
                    break;
                case HEMS_ID::HEMS_3:
                    current_control = CurrentControl(actuators.HEMS3);
                    break;
                case HEMS_ID::EMS_1:
                    current_control = CurrentControl(actuators.EMS1);
                    break;
                case HEMS_ID::EMS_3:
                    current_control = CurrentControl(actuators.EMS3);
                    break;
                default:
                    ErrorHandler("Invalid HEMS_ID, given id: %d", hems_id);
                    break;
            }
            current_control.half_bridge.turn_on();
        }

        void execute_distance_control(float real_distance){
        	distance_control.control(real_distance);
        }

        void execute_current_control(float real_current){
        	current_control.set_reference_current(distance_control.pid.output_value);
        	current_control.control(real_current);
        }

        void set_distance_reference(float new_distance){
        	distance_control.set_reference_distance(new_distance/1000);
        }

        void stop(){
            current_control.half_bridge.turn_off();
        }

        void reset(){
        	distance_control.pid.reset();
        	current_control.current_pi.reset();
        	current_control.half_bridge.turn_on();
        }
    };
}


