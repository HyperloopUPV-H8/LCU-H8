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

	float airgaps[8] = {0.0};

	double reference_current_hems_1 = 0;
	double reference_current_hems_3 = 0;
	double reference_current_ems_1 = 0;
	double reference_current_ems_3 = 0;
	};

	template<> class Data<TESTBENCH_1DOF>{
	public:
	float coil_current = 0;

	float coil_temp = 0;

	float lpu_temp = 0;

	float batt_voltage = 0;

	float airgap = 0.0;

	double reference_current = 0;
	};

	template<> class Data<VEHICLE_5DOF>{
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

	float airgaps[8] = {0.0};

	float reference_currents[8] = {0.0};

	};
}
