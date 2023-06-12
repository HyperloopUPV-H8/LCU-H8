#pragma once
#include "LCU_Data/LCU_Data.hpp"
#include "LCU_Pinout/Pinout.hpp"
#include "Control/Blocks/MovingAverage.hpp"
#include "Sensors/LinearSensor/FilteredLinearSensor.hpp"
#include "Protections/Boundary.hpp"
#include "Control/Blocks/Zeroing.hpp"
#include "Sensors/Common/PT100.hpp"
namespace LCU{

    class Sensors{
        public:
            Data& data;

            // Airgaps
            static constexpr float airgap_slope_vertical = 8.7103;
            static constexpr float airgap_offset_vertical = 96.983;
            static constexpr float airgap_slope_horitonzal = 47.789;
            static constexpr float airgap_offset_horizontal = 45.783;

            static constexpr size_t aigarp_filter_order = 10;
            MovingAverage<aigarp_filter_order> airgap_2_filter;
            MovingAverage<aigarp_filter_order> airgap_4_filter;
            MovingAverage<aigarp_filter_order> airgap_6_filter;
            MovingAverage<aigarp_filter_order> airgap_8_filter;
            FilteredLinearSensor<float,aigarp_filter_order> airgap_2_sensor {Pinout::AIRGAP_2_PIN, airgap_slope_vertical, airgap_offset_vertical, data.airgaps[2-1], airgap_2_filter};
            FilteredLinearSensor<float,aigarp_filter_order> airgap_4_sensor {Pinout::AIRGAP_4_PIN, airgap_slope_vertical, airgap_offset_vertical, data.airgaps[4-1], airgap_4_filter};
            FilteredLinearSensor<float,aigarp_filter_order> airgap_6_sensor {Pinout::AIRGAP_6_PIN, airgap_slope_horitonzal, airgap_offset_horizontal, data.airgaps[6-1], airgap_6_filter};
            FilteredLinearSensor<float,aigarp_filter_order> airgap_8_sensor {Pinout::AIRGAP_8_PIN, airgap_slope_horitonzal, airgap_offset_horizontal, data.airgaps[8-1], airgap_8_filter};

            // Curents
            static constexpr float current_slope = 56.222;
            static constexpr float current_offset = -91.505;

            static constexpr size_t current_filter_order = 20;
            MovingAverage<current_filter_order> current_hems_2_filter;
            MovingAverage<current_filter_order> current_hems_4_filter;
            MovingAverage<current_filter_order> current_ems_2_filter;
            MovingAverage<current_filter_order> current_ems_4_filter;
            FilteredLinearSensor<float,current_filter_order> current_hems_2_sensor {Pinout::HEMS2_CURRENT_PIN, current_slope, current_offset, data.coil_current_hems_2 ,current_hems_2_filter};
            FilteredLinearSensor<float,current_filter_order> current_hems_4_sensor {Pinout::HEMS4_CURRENT_PIN, current_slope, current_offset, data.coil_current_hems_4, current_hems_4_filter};
            FilteredLinearSensor<float,current_filter_order> current_ems_2_sensor {Pinout::EMS2_CURRENT_PIN, current_slope, current_offset, data.coil_current_ems_2, current_ems_2_filter};
            FilteredLinearSensor<float,current_filter_order> current_ems_4_sensor {Pinout::EMS4_CURRENT_PIN, current_slope, current_offset, data.coil_current_ems_4, current_ems_4_filter};


            static constexpr size_t zeroing_order = 10000;
            static constexpr float max_zeroing_current = 5.0;
            Zeroing<float, zeroing_order> hems_2_zeroing{current_hems_2_sensor, max_zeroing_current};
            Zeroing<float, zeroing_order> hems_4_zeroing{current_hems_4_sensor, max_zeroing_current};
            Zeroing<float, zeroing_order> ems_2_zeroing{current_ems_2_sensor, max_zeroing_current};
            Zeroing<float, zeroing_order> ems_4_zeroing{current_ems_4_sensor, max_zeroing_current};

			 // Temparatures
           static constexpr size_t temperature_filter_order = 10;
           MovingAverage<temperature_filter_order> hems_2_temperature_filter;
           MovingAverage<temperature_filter_order> hems_4_temperature_filter;
           MovingAverage<temperature_filter_order> ems_2_temperature_filter;
           MovingAverage<temperature_filter_order> ems_4_temperature_filter;
           PT100<temperature_filter_order> hems_2_temperature_sensor{Pinout::HEMS2_TEMP_PIN, data.hems_2_temperature,hems_2_temperature_filter};
           PT100<temperature_filter_order> hems_4_temperature_sensor{Pinout::HEMS4_TEMP_PIN, data.hems_4_temperature,hems_4_temperature_filter};
           PT100<temperature_filter_order> ems_2_temperature_sensor{Pinout::EMS2_TEMP_PIN, data.ems_2_temperature,ems_2_temperature_filter};
           PT100<temperature_filter_order> ems_4_temperature_sensor{Pinout::EMS4_TEMP_PIN, data.ems_4_temperature,ems_4_temperature_filter};

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

            void current_zeroing(){
            	hems_2_zeroing.execute();
            	hems_4_zeroing.execute();
            	ems_2_zeroing.execute();
            	ems_4_zeroing.execute();
            }

            void read_temps(){
            	hems_2_temperature_sensor.read();
            	hems_4_temperature_sensor.read();
            	ems_2_temperature_sensor.read();
            	ems_4_temperature_sensor.read();
            }
    };

} 
