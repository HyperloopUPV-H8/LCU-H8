#pragma once
#include "LCU_Actuators/LCU_Actuators.hpp"
#include "LCU_Data/LCU_Data.hpp"
#include "CurrentControl.hpp"

namespace LCU {
	class Control{
	public:
    	CurrentControl hems_2_current_control, hems_4_current_control, ems_2_current_control, ems_4_current_control;
    	float& hems_2_current, &hems_4_current, &ems_2_current, &ems_4_current;
    	Control(LCU::Actuators& actuators, LCU::Data& data): hems_2_current_control(actuators.HEMS_2,data.reference_currents[COIL_ID::HEMS_2]),
    			hems_4_current_control(actuators.HEMS_4, data.reference_currents[COIL_ID::HEMS_4]),
    			ems_2_current_control(actuators.EMS_2, data.reference_currents[COIL_ID::EMS_2]),
				ems_4_current_control(actuators.EMS_4, data.reference_currents[COIL_ID::EMS_4]),
				hems_2_current(data.coil_current_hems_2),
				hems_4_current(data.coil_current_hems_4),
				ems_2_current(data.coil_current_ems_2),
				ems_4_current(data.coil_current_ems_4)
    	{}

    	void execute_current_control(){
    		hems_2_current_control.control(hems_2_current);
    		hems_4_current_control.control(hems_4_current);
			ems_2_current_control.control(ems_2_current);
			ems_4_current_control.control(ems_4_current);
			hems_2_current_control.apply_control();
			hems_4_current_control.apply_control();
			ems_2_current_control.apply_control();
			ems_4_current_control.apply_control();
    	}

    	void stop(){
    		hems_2_current_control.half_bridge.turn_off();
    		hems_4_current_control.half_bridge.turn_off();
			ems_2_current_control.half_bridge.turn_off();
			ems_4_current_control.half_bridge.turn_off();
    	}

    	void reset(){
    		hems_2_current_control.reset();
    		hems_4_current_control.reset();
    		ems_2_current_control.reset();
    		ems_4_current_control.reset();
    		hems_2_current_control.half_bridge.turn_on();
    		hems_4_current_control.half_bridge.turn_on();
			ems_2_current_control.half_bridge.turn_on();
			ems_4_current_control.half_bridge.turn_on();
    	}

    	void change_current_reference(COIL_ID coil_id, float new_reference){
       		switch(coil_id){
       		case COIL_ID::HEMS_2:
           		hems_2_current_control.set_reference_current(new_reference);
       		case COIL_ID::HEMS_4:
           		hems_4_current_control.set_reference_current(new_reference);
       		case COIL_ID::EMS_2:
           		ems_2_current_control.set_reference_current(new_reference);
       		case COIL_ID::EMS_4:
           		ems_4_current_control.set_reference_current(new_reference);
       		default:
       			ErrorHandler("Coil current control not supported %d", coil_id);
       		}
       	}

       	void execute_current_control(COIL_ID coil_id){
       		switch(coil_id){
       		case COIL_ID::HEMS_2:
           		hems_2_current_control.control(hems_2_current);
       			hems_2_current_control.apply_control();
       		case COIL_ID::HEMS_4:
           		hems_4_current_control.control(hems_4_current);
       			hems_4_current_control.apply_control();
       		case COIL_ID::EMS_2:
           		ems_2_current_control.control(ems_2_current);
       			ems_2_current_control.apply_control();
       		case COIL_ID::EMS_4:
           		ems_4_current_control.control(ems_4_current);
       			ems_4_current_control.apply_control();
       		default:
       			ErrorHandler("Coil current control not supported %d", coil_id);
       		}
       	}
	};
}


