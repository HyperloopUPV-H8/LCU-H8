#pragma once
#include "LCU_Mode/LCU_Mode.hpp"
namespace LCU{
	template<LCU::MASTER_MODE> class Data;

	template<> class Data<LPU_VALIDATION>{
	public:
	float coil_current_hems_1 = 0;
	float coil_current_hems_3 = 0;
	float coil_current_ems_1 = 0;
	float coil_current_ems_3  = 0;

	float coil_temp_1 = 0;
	float coil_temp_2 = 0;
	float coil_temp_3 = 0;
	float coil_temp_4 = 0;

	float lpu_temp_1 = 0;
	float lpu_temp_2 = 0;
	float lpu_temp_3 = 0;
	float lpu_temp_4 = 0;

	float batt_voltage_1 = 0;
	float batt_voltage_2 = 0;

	float airgap_1 = 0;
	float airgap_3 = 0;
	float airgap_5 = 0;
	float airgap_7 = 0;;

	double reference_current_hems_1 = 0;
	double reference_current_hems_3 = 0;
	double reference_current_ems_1 = 0;
	double reference_current_ems_3 = 0;
	};
}
