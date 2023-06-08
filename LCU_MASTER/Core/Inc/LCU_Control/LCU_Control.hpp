#pragma once
#include <LCU_Control/DistanceControl.hpp>
#include "LCU_Actuators/LCU_Actuators.hpp"
#include "DistanceControl.hpp"
#include "LCU_Mode/LCU_Mode.hpp"
#include "LCU_Data/LCU_Data.hpp"
#include "CurrentControl.hpp"
#include "ErrorHandler/ErrorHandler.hpp"

namespace LCU {
    template<LCU::MASTER_MODE> class Control;

    template<> class Control<LCU::MASTER_MODE::LPU_VALIDATION>{
        public:
            CurrentControl current_control;
            Actuators<LPU_VALIDATION>& actuators;
            Data<LPU_VALIDATION>& data;
            float* current_value;
            COIL_ID coil_id;
            Control(LCU::Actuators<LPU_VALIDATION>& actuators, LCU::Data<LPU_VALIDATION>& data, COIL_ID hems_id) : actuators(actuators), data(data){
            	change_coil_id(hems_id);
            }

            void change_coil_id(COIL_ID id){
                switch (id){
                    case COIL_ID::HEMS_1:
                        current_control = {actuators.HEMS_1, data.reference_current_hems_1};
                        current_value = &data.coil_current_hems_1;
                        break;
                    case COIL_ID::HEMS_3:
                        current_control = {actuators.HEMS_3, data.reference_current_hems_3};
                        current_value = &data.coil_current_hems_3;
                        break;
                    case COIL_ID::EMS_1:
                        current_control = {actuators.EMS_1, data.reference_current_ems_1};
                        current_value = &data.coil_current_ems_1;
                        break;
                    case COIL_ID::EMS_3:
                        current_control = {actuators.EMS_3, data.reference_current_ems_3};
                        current_value = &data.coil_current_ems_3;
                        break;
                    default:
                        ErrorHandler("Invalid HEMS_ID, given id: %d", id);
                        current_value = nullptr;
                        return;
                        break;
                }
                coil_id = id;
            }

            void execute(float real_current){
                current_control.control(real_current);
            }

            void set_reference(float reference){
                current_control.set_reference_current(reference);
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
        Control(LCU::Actuators<LPU_VALIDATION>& actuators, LCU::Data<TESTBENCH_1DOF>& data, COIL_ID hems_id){
            switch (hems_id){
                case COIL_ID::HEMS_1:
                    current_control = {actuators.HEMS_1,data.reference_current};
                    break;
                case COIL_ID::HEMS_3:
                    current_control = {actuators.HEMS_3, data.reference_current};
                    break;
                case COIL_ID::EMS_1:
                    current_control = {actuators.EMS_1, data.reference_current};
                    break;
                case COIL_ID::EMS_3:
                    current_control = {actuators.EMS_3, data.reference_current};
                    break;
                default:
                    ErrorHandler("Invalid HEMS_ID, given id: %d", hems_id);
                    break;
            }
        }

        void execute_distance_control(float real_distance){
        	distance_control.control(real_distance);
        }

        void execute_current_control(float real_current){
        	current_control.set_reference_current(distance_control.pid.output_value);
        	current_control.control(real_current);
        	current_control.apply_control();
        }

        void set_distance_reference(float new_distance){
        	distance_control.set_reference_distance(new_distance/1000);
        }

        void stop(){
            current_control.half_bridge.turn_off();
        }

        void reset(){
        	distance_control.reset();
        	current_control.reset();
        	current_control.half_bridge.turn_on();
        }
    };

    template<> class Control<LCU::MASTER_MODE::VEHICLE_5DOF>{
    public:
    	CurrentControl hems_1_current_control, hems_3_current_control, ems_1_current_control, ems_3_current_control;
    	DistanceControl<VEHICLE_5DOF> position_control;
    	float& hems_1_current, &hems_3_current, &ems_1_current, &ems_3_current;
    	Data<VEHICLE_5DOF>& data;


    	Control(LCU::Actuators<VEHICLE_5DOF>& actuators, LCU::Data<VEHICLE_5DOF>& data): hems_1_current_control(actuators.HEMS_1,data.reference_currents[COIL_ID::HEMS_1]),
    			hems_3_current_control(actuators.HEMS_3, data.reference_currents[COIL_ID::HEMS_3]),
    			ems_1_current_control(actuators.EMS_1, data.reference_currents[COIL_ID::EMS_1]),
				ems_3_current_control(actuators.EMS_3, data.reference_currents[COIL_ID::EMS_3]),
    			position_control(data.airgaps, data.reference_currents),
				hems_1_current(data.coil_current_hems_1),
				hems_3_current(data.coil_current_hems_3),
				ems_1_current(data.coil_current_ems_1),
				ems_3_current(data.coil_current_ems_3),
				data(data)
    	{}

    	void set_z_reference(float new_reference){
    		position_control.set_z_reference(new_reference);
    	}

    	void execute_current_control(){
    		hems_1_current_control.control(hems_1_current);
    		hems_3_current_control.control(hems_3_current);
			ems_1_current_control.control(ems_1_current);
			ems_3_current_control.control(ems_3_current);
			hems_1_current_control.apply_control();
			hems_3_current_control.apply_control();
			ems_1_current_control.apply_control();
			ems_3_current_control.apply_control();
    	}

    	void execute_distance_control(){
    		position_control.control();
    	}

    	void stop(){
    		hems_1_current_control.half_bridge.turn_off();
    		hems_3_current_control.half_bridge.turn_off();
			ems_1_current_control.half_bridge.turn_off();
			ems_3_current_control.half_bridge.turn_off();
   			for(float& reference_current : data.reference_currents) reference_current = 0.0;
    	}

    	void reset(){
    		hems_1_current_control.reset();
    		hems_3_current_control.reset();
    		ems_1_current_control.reset();
    		ems_3_current_control.reset();
    		position_control.reset();
   			for(float& reference_current : data.reference_currents) reference_current = 0.0;
    		hems_1_current_control.half_bridge.turn_on();
    		hems_3_current_control.half_bridge.turn_on();
			ems_1_current_control.half_bridge.turn_on();
			ems_3_current_control.half_bridge.turn_on();
    	}
    };

    template<> class Control<LCU::MASTER_MODE::VEHICLE_TESTING>{
       public:
       	CurrentControl hems_1_current_control, hems_3_current_control, ems_1_current_control, ems_3_current_control;
       	float& hems_1_current, &hems_3_current, &ems_1_current, &ems_3_current;
    	double y = 0, z = 0, rotation_x = 0, rotation_y = 0, rotation_z = 0;
    	Data<VEHICLE_TESTING>& data;

       	Control(LCU::Actuators<VEHICLE_TESTING>& actuators, LCU::Data<VEHICLE_TESTING>& data): hems_1_current_control(actuators.HEMS_1,data.reference_currents[COIL_ID::HEMS_1]),
       			hems_3_current_control(actuators.HEMS_3, data.reference_currents[COIL_ID::HEMS_3]),
       			ems_1_current_control(actuators.EMS_1, data.reference_currents[COIL_ID::EMS_1]),
   				ems_3_current_control(actuators.EMS_3, data.reference_currents[COIL_ID::EMS_3]),
   				hems_1_current(data.coil_current_hems_1),
   				hems_3_current(data.coil_current_hems_3),
   				ems_1_current(data.coil_current_ems_1),
   				ems_3_current(data.coil_current_ems_3),
				data(data)
       	{}

       	void change_current_reference(COIL_ID coil_id, float new_reference){
       		switch(coil_id){
       		case COIL_ID::HEMS_1:
           		hems_1_current_control.set_reference_current(new_reference);
           		break;
       		case COIL_ID::HEMS_3:
           		hems_3_current_control.set_reference_current(new_reference);
           		break;
       		case COIL_ID::EMS_1:
           		ems_1_current_control.set_reference_current(new_reference);
           		break;
       		case COIL_ID::EMS_3:
           		ems_3_current_control.set_reference_current(new_reference);
           		break;
       		default:
       			ErrorHandler("Coil current control not supported %d", coil_id);
       		}
       	}

       	void execute_current_control(COIL_ID coil_id){
       		switch(coil_id){
       		case COIL_ID::HEMS_1:
           		hems_1_current_control.control(hems_1_current);
       			hems_1_current_control.apply_control();
       			break;
       		case COIL_ID::HEMS_3:
           		hems_3_current_control.control(hems_3_current);
       			hems_3_current_control.apply_control();
       			break;
       		case COIL_ID::EMS_1:
           		ems_1_current_control.control(ems_1_current);
       			ems_1_current_control.apply_control();
       			break;
       		case COIL_ID::EMS_3:
           		ems_3_current_control.control(ems_3_current);
       			ems_3_current_control.apply_control();
       			break;
       		default:
       			ErrorHandler("Coil current control not supported %d", coil_id);
       		}
       	}

       	void execute_current_control(){
       		hems_1_current_control.control(hems_1_current);
       		hems_3_current_control.control(hems_3_current);
   			ems_1_current_control.control(ems_1_current);
   			ems_3_current_control.control(ems_3_current);
   			hems_1_current_control.apply_control();
   			hems_3_current_control.apply_control();
   			ems_1_current_control.apply_control();
   			ems_3_current_control.apply_control();
       	}

       	void stop(){
       		hems_1_current_control.half_bridge.turn_off();
       		hems_3_current_control.half_bridge.turn_off();
   			ems_1_current_control.half_bridge.turn_off();
   			ems_3_current_control.half_bridge.turn_off();
   			for(float& reference_current : data.reference_currents) reference_current = 0.0;
       	}

       	void reset(){
       		hems_1_current_control.reset();
       		hems_3_current_control.reset();
       		ems_1_current_control.reset();
       		ems_3_current_control.reset();
   			for(float& reference_current : data.reference_currents) reference_current = 0.0;
       		hems_1_current_control.half_bridge.turn_on();
       		hems_3_current_control.half_bridge.turn_on();
   			ems_1_current_control.half_bridge.turn_on();
   			ems_3_current_control.half_bridge.turn_on();
       	}
       };

}


