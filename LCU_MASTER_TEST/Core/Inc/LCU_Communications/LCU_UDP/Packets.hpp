#pragma once

#include "../../LCU_MASTER.hpp"

namespace LCU{
	template<MASTER_MODE> class Packets;

	template<>
	class Packets<LPU_VALIDATION>{
	public:
		//TO VCU
		StackPacket<16,float,float,float,float> airgaps_data;

		StackPacket<16,float,float,float,float> coil_currents;
//
//		StackPacket<32,float,float,float,float,float,float,float,float> coil_temperatures;
//
//		StackPacket<32,float,float,float,float,float,float,float,float> lpu_temperatures;

		StackPacket<8,float,float> battery_data;

		Packets(Data<LPU_VALIDATION>& data) : airgaps_data(307, &data.airgaps[0],&data.airgaps[2],&data.airgaps[4],&data.airgaps[6]),
				coil_currents(313, &data.coil_current_hems_1, &data.coil_current_ems_1, &data.coil_current_hems_3, &data.coil_current_ems_3),
				battery_data(312, &data.batt_voltage_1, &data.batt_voltage_2){}

	};

	template<>
	class Packets<VEHICLE_5DOF>{
	public:

		//TO VCU
		StackPacket<32,float,float,float,float,float,float,float,float> airgaps_data;

		StackPacket<32,float,float,float,float,float,float,float,float> coil_currents;
//
		StackPacket<32,float,float,float,float,float,float,float,float> coil_temperatures;

		StackPacket<112, float, float, float, float, float, float, float, float, float, float, float, float, float, double, double, double, double, double, uint32_t> levitation_data;
//
//		StackPacket<32,float,float,float,float,float,float,float,float> lpu_temperatures;

		//StackPacket<16,float,float,float,float> battery_data;

		//TO SLAVE
		StackPacket<16,float,float,float,float> slave_reference_currents;

		StackPacket<16,float,float,float,float> slave_airgaps;

		StackPacket<16,float,float,float,float> slave_currents;
//
		StackPacket<16,float,float,float,float> slave_coil_temperatures;
//
//		StackPacket<16,float,float,float,float> slave_lpu_temperatures;
//
//		StackPacket<8,float,float> slave_lpu_batteries;


		Packets(Data<VEHICLE_5DOF>& data, Control<VEHICLE_5DOF>& control) : airgaps_data(307, &data.airgaps[0],&data.airgaps[1],&data.airgaps[2],&data.airgaps[3],&data.airgaps[4],&data.airgaps[5],&data.airgaps[6],&data.airgaps[7]),
				coil_currents(313, &data.coil_current_hems_1, &data.slave_coil_current_hems_2, &data.coil_current_hems_3, &data.slave_coil_current_hems_4, &data.coil_current_ems_1, &data.slave_coil_current_ems_2, &data.coil_current_ems_3, &data.slave_coil_current_ems_4),
				coil_temperatures(310, &data.hems_1_temperature, &data.slave_hems_2_temperature, &data.hems_3_temperature, &data.slave_hems_4_temperature,
						&data.ems_1_temperature, &data.slave_ems_2_temperature, &data.ems_3_temperature, &data.slave_ems_4_temperature),
				levitation_data(311, &data.reference_currents[0],&data.reference_currents[1],&data.reference_currents[2],&data.reference_currents[3],
						&data.reference_currents[4],&data.reference_currents[5],&data.reference_currents[6],&data.reference_currents[7],
						&control.position_control.levitation_position.y, &control.position_control.levitation_position.z, &control.position_control.levitation_position.rotation_x, &control.position_control.levitation_position.rotation_y, &control.position_control.levitation_position.rotation_z,
						&control.position_control.y_filter_derivative.output_value, &control.position_control.z_filter_derivative.output_value,&control.position_control.rot_x_filter_derivative.output_value, &control.position_control.rot_y_filter_derivative.output_value,&control.position_control.rot_z_filter_derivative.output_value,
						&control.distance_control_counter),
				slave_reference_currents(309, &data.reference_currents[COIL_ID::HEMS_2],&data.reference_currents[COIL_ID::HEMS_4],&data.reference_currents[COIL_ID::EMS_2],&data.reference_currents[COIL_ID::EMS_4]),
				slave_airgaps(408, &data.airgaps[2-1],  &data.airgaps[4-1],  &data.airgaps[6-1], &data.airgaps[8-1]),
				slave_currents(410, &data.slave_coil_current_hems_2, &data.slave_coil_current_hems_4, &data.slave_coil_current_ems_2, &data.slave_coil_current_ems_4),
				slave_coil_temperatures(411, &data.slave_hems_2_temperature, &data.slave_hems_4_temperature, &data.slave_ems_2_temperature, &data.slave_ems_4_temperature)
		{ }

	};

	template<>
	class Packets<VEHICLE_TESTING>{
	public:

		//TO VCU
		StackPacket<32,float,float,float,float,float,float,float,float> airgaps_data;

		StackPacket<32,float,float,float,float,float,float,float,float> coil_currents;
//
		StackPacket<32,float,float,float,float,float,float,float,float> coil_temperatures;

		StackPacket<72, float, float, float, float, float, float, float, float, float, float, float, float, float> levitation_data;
//
//		StackPacket<32,float,float,float,float,float,float,float,float> lpu_temperatures;

		//StackPacket<16,float,float,float,float> battery_data;

		//TO SLAVE
		StackPacket<16,float,float,float,float> slave_reference_currents;

		StackPacket<16,float,float,float,float> slave_airgaps;

		StackPacket<16,float,float,float,float> slave_currents;
//
		StackPacket<16,float,float,float,float> slave_coil_temperatures;
//
//		StackPacket<16,float,float,float,float> slave_lpu_temperatures;
//
//		StackPacket<8,float,float> slave_lpu_batteries;


		Packets(Data<VEHICLE_TESTING>& data, Control<VEHICLE_TESTING>& control) : airgaps_data(307, &data.airgaps[0],&data.airgaps[1],&data.airgaps[2],&data.airgaps[3],&data.airgaps[4],&data.airgaps[5],&data.airgaps[6],&data.airgaps[7]),
				coil_currents(313, &data.coil_current_hems_1, &data.slave_coil_current_hems_2, &data.coil_current_hems_3, &data.slave_coil_current_hems_4, &data.coil_current_ems_1, &data.slave_coil_current_ems_2, &data.coil_current_ems_3, &data.slave_coil_current_ems_4),
				coil_temperatures(310, &data.hems_1_temperature, &data.slave_hems_2_temperature, &data.hems_3_temperature, &data.slave_hems_4_temperature,
						&data.ems_1_temperature, &data.slave_ems_2_temperature, &data.ems_3_temperature, &data.slave_ems_4_temperature),
				levitation_data(311, &data.reference_currents[0],&data.reference_currents[1],&data.reference_currents[2],&data.reference_currents[3],
						&data.reference_currents[4],&data.reference_currents[5],&data.reference_currents[6],&data.reference_currents[7],
						&control.y, &control.z, &control.rotation_x, &control.rotation_y, &control.rotation_z),
				slave_reference_currents(309, &data.reference_currents[COIL_ID::HEMS_2],&data.reference_currents[COIL_ID::HEMS_4],&data.reference_currents[COIL_ID::EMS_2],&data.reference_currents[COIL_ID::EMS_4]),
				slave_airgaps(408, &data.airgaps[2-1],  &data.airgaps[4-1],  &data.airgaps[6-1], &data.airgaps[8-1]),
				slave_currents(410, &data.slave_coil_current_hems_2, &data.slave_coil_current_hems_4, &data.slave_coil_current_ems_2, &data.slave_coil_current_ems_4),
				slave_coil_temperatures(411, &data.slave_hems_2_temperature, &data.slave_hems_4_temperature, &data.slave_ems_2_temperature, &data.slave_ems_4_temperature)
		{ }

	};
}