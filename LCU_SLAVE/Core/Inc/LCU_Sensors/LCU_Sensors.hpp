#pragma once
#include "LCU_Data/LCU_Data.hpp"
#include "LCU_Pinout/Pinout.hpp"
#include "Control/Blocks/MovingAverage.hpp"
#include "Sensors/LinearSensor/FilteredLinearSensor.hpp"
#include "Protections/Boundary.hpp"
namespace LCU{

    class Sensors{
        public:
            Data& data;
            // Airgaps
            static constexpr float airgap_slope = 17.23477;
            static constexpr float airgap_offset = 50.45231;
            static constexpr float offset_mecanico = 63.303;
            static constexpr size_t aigarp_filter_order = 10;
            MovingAverage<aigarp_filter_order> airgap_2_filter;
            MovingAverage<aigarp_filter_order> airgap_4_filter;
            MovingAverage<aigarp_filter_order> airgap_6_filter;
            MovingAverage<aigarp_filter_order> airgap_8_filter;
            FilteredLinearSensor<float,aigarp_filter_order> airgap_2_sensor {Pinout::AIRGAP_2_PIN, airgap_slope, airgap_offset - offset_mecanico, data.airgaps[2-1], airgap_2_filter};
            FilteredLinearSensor<float,aigarp_filter_order> airgap_4_sensor {Pinout::AIRGAP_4_PIN, airgap_slope, airgap_offset - offset_mecanico, data.airgaps[4-1], airgap_4_filter};
            FilteredLinearSensor<float,aigarp_filter_order> airgap_6_sensor {Pinout::AIRGAP_6_PIN, airgap_slope, airgap_offset - offset_mecanico, data.airgaps[6-1], airgap_6_filter};
            FilteredLinearSensor<float,aigarp_filter_order> airgap_8_sensor {Pinout::AIRGAP_8_PIN, airgap_slope, airgap_offset - offset_mecanico, data.airgaps[8-1], airgap_8_filter};

            // Curents
            static constexpr float current_slope = 44.746;
            static constexpr float current_offset = -85.72;

            static constexpr size_t current_filter_order = 20;
            MovingAverage<current_filter_order> current_hems_2_filter;
            MovingAverage<current_filter_order> current_hems_4_filter;
            MovingAverage<current_filter_order> current_ems_2_filter;
            MovingAverage<current_filter_order> current_ems_4_filter;
            FilteredLinearSensor<float,current_filter_order> current_hems_2_sensor {Pinout::HEMS2_CURRENT_PIN, current_slope, current_offset, data.coil_current_hems_2 ,current_hems_2_filter};
            FilteredLinearSensor<float,current_filter_order> current_hems_4_sensor {Pinout::HEMS4_CURRENT_PIN, current_slope, current_offset, data.coil_current_hems_4, current_hems_4_filter};
            FilteredLinearSensor<float,current_filter_order> current_ems_2_sensor {Pinout::EMS2_CURRENT_PIN, current_slope, current_offset, data.coil_current_ems_2, current_ems_2_filter};
            FilteredLinearSensor<float,current_filter_order> current_ems_4_sensor {Pinout::EMS4_CURRENT_PIN, current_slope, current_offset, data.coil_current_ems_4, current_ems_4_filter};

            //Temparatures
//            static constexpr float temperature_slope;
//            static constexpr float temperature_offset;
//
//            static constexpr size_t temperature_filter_order = 10;
//            MovingAverage<temperature_filter_order> hems_1_temperature_filter;
//            MovingAverage<temperature_filter_order> hems_3_temperature_filter;
//            MovingAverage<temperature_filter_order> ems_1_temperature_filter;
//            MovingAverage<temperature_filter_order> ems_3_temperature_filter;
//            FilteredLinearSensor<temperature_filter_order> hems_1_temperature_sensor {Pinout::HEMS1_TEMP_PIN, temperature_slope, temperature_offset, data.hems_1_temperature};
//            FilteredLinearSensor<temperature_filter_order> hems_3_temperature_sensor {Pinout::HEMS3_TEMP_PIN, temperature_slope, temperature_offset, data.hems_3_temperature};
//            FilteredLinearSensor<temperature_filter_order> ems_1_temperature_sensor {Pinout::EMS1_TEMP_PIN, temperature_slope, temperature_offset, data.ems_1_temperature};
//            FilteredLinearSensor<temperature_filter_order> ems_3_temperature_sensor {Pinout::EMS3_TEMP_PIN, temperature_slope, temperature_offset, data.ems_3_temperature};

            Sensors(Data& data) : data(data) {};

            void read_currents(){
            	current_hems_2_sensor.read();
            	current_hems_4_sensor.read();
            	current_ems_2_sensor.read();
            	current_ems_4_sensor.read();
            	hems_2_time_protection->check_accumulation(data.coil_current_hems_2);
            	hems_4_time_protection->check_accumulation(data.coil_current_hems_4);
            }

            void read_airgaps(){
            	airgap_2_sensor.read();
            	airgap_4_sensor.read();
            	airgap_6_sensor.read();
            	airgap_8_sensor.read();
            }

//            void read_temps(){
//            	hems_1_temperature_sensor.read();
//            	hems_3_temperature_sensor.read();
//            	ems_1_temperature_sensor.read();
//            	ems_3_temperature_sensor.read();
//            }
    };

} 
