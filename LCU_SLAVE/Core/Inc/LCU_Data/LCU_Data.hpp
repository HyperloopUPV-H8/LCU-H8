#pragma once
#include "Protections/ProtectionManager.hpp"
namespace LCU{


	constexpr float max_persistent_current = 30;
	constexpr float current_frequency = 10000;
	constexpr float time_limit = 5;
	constexpr float min_hems_current = -40, max_hems_current = 40;
	constexpr float min_ems_current = -25, max_ems_current = 25;
	constexpr float max_coil_temperature = 40;
	constexpr float min_battery_voltage = 190, max_battery_voltage = 260;
	constexpr float max_lpu_temperature = 65;

	Boundary<float,TIME_ACCUMULATION>* hems_2_time_protection = nullptr;
	Boundary<float,TIME_ACCUMULATION>* hems_4_time_protection = nullptr;

	class Data{
	public:
	float coil_current_hems_2 = 0;
	float coil_current_hems_4 = 0;
	float coil_current_ems_2 = 0;
	float coil_current_ems_4  = 0;

	float hems_2_temperature = 0;
	float hems_4_temperature = 0;
	float ems_2_temperature = 0;
	float ems_4_temperature = 0;

	float lpu_temp_1 = 0;
	float lpu_temp_2 = 0;
	float lpu_temp_3 = 0;
	float lpu_temp_4 = 0;

	float batt_voltage_1 = 0;
	float batt_voltage_2 = 0;

	float airgaps[8] = {0.0};

	float reference_currents[8] = {0.0};

	void add_protections(){
		add_protection(&coil_current_hems_2, Boundary<float, TIME_ACCUMULATION>(max_persistent_current,time_limit,current_frequency, hems_2_time_protection),
											 Boundary<float, OUT_OF_RANGE>(min_hems_current,max_hems_current));

		add_protection(&coil_current_hems_4, Boundary<float, TIME_ACCUMULATION>(max_persistent_current, time_limit, current_frequency, hems_4_time_protection),
											 Boundary<float, OUT_OF_RANGE>(min_hems_current,max_hems_current));

		add_protection(&coil_current_ems_2, Boundary<float,OUT_OF_RANGE>(min_ems_current,max_ems_current));

		add_protection(&coil_current_ems_4, Boundary<float,OUT_OF_RANGE>(min_ems_current,max_ems_current));

		add_protection(&hems_2_temperature, Boundary<float, ABOVE>(max_coil_temperature));
		add_protection(&hems_4_temperature, Boundary<float, ABOVE>(max_coil_temperature));
		add_protection(&ems_2_temperature, Boundary<float, ABOVE>(max_coil_temperature));
		add_protection(&ems_4_temperature, Boundary<float, ABOVE>(max_coil_temperature));

		add_protection(&batt_voltage_1, Boundary<float, OUT_OF_RANGE>(min_battery_voltage,max_battery_voltage));
		add_protection(&batt_voltage_2, Boundary<float, OUT_OF_RANGE>(min_battery_voltage,max_battery_voltage));

		add_protection(&lpu_temp_1, Boundary<float, ABOVE>(max_lpu_temperature));
		add_protection(&lpu_temp_2, Boundary<float, ABOVE>(max_lpu_temperature));
		add_protection(&lpu_temp_3, Boundary<float, ABOVE>(max_lpu_temperature));
		add_protection(&lpu_temp_4, Boundary<float, ABOVE>(max_lpu_temperature));
	}

	};
}