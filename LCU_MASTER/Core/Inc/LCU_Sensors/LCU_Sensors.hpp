#pragma once
#include "LCU_Mode/LCU_Mode.hpp"
#include "LCU_Data/LCU_Data.hpp"
#include "LCU_Pinout/Pinout.hpp"
#include "Control/Blocks/MovingAverage.hpp"
#include "Sensors/LinearSensor/LinearSensor.hpp"
#include "Protections/Boundary.hpp"
namespace LCU{
    template<LCU::MASTER_MODE> class Sensors;

    template<MASTER_MODE::LPU_VALIDATION> class Sensors{
        public:
            Data<LPU_VALIDATION>& data;
            // Airgaps
            static constexpr float airgap_slope;
            static constexpr float airgap_offset;
            static constexpr float offset_mecanico;
            MovingAverage<10> airgap_1_filter;
            MovingAverage<10> airgap_3_filter;
            MovingAverage<10> airgap_5_filter;
            MovingAverage<10> airgap_7_filter;
            LinearSensor airgap_1_sensor {Pinout::AIRGAP_1_PIN, airgap_slope, airgap_offset};
            LinearSensor airgap_3_sensor {Pinout::AIRGAP_3_PIN, airgap_slope, airgap_offset};
            LinearSensor airgap_5_sensor {Pinout::AIRGAP_5_PIN, airgap_slope, airgap_offset};
            LinearSensor airgap_7_sensor {Pinout::AIRGAP_7_PIN, airgap_slope, airgap_offset};

            // Curents
            static constexpr float current_slope;
            static constexpr float current_offset;
            static constexpr float current_read_frequency = 10000;
            static constexpr float max_persistent_current = 27;
            static constexpr float time_limit = 5;
            MovingAverage<20> current_hems_1_filter;
            MovingAverage<20> current_hems_3_filter;
            MovingAverage<20> current_ems_1_filter;
            MovingAverage<20> current_ems_3_filter;
            LinearSensor current_hems_1_sensor {Pinout::HEMS1_CURRENT_PIN, current_slope, current_offset};
            LinearSensor current_hems_3_sensor {Pinout::HEMS3_CURRENT_PIN, current_slope, current_offset};
            LinearSensor current_ems_1_sensor {Pinout::EMS1_CURRENT_PIN, current_slope, current_offset};
            LinearSensor current_ems_3_sensor {Pinout::EMS3_CURRENT_PIN, current_slope, current_offset};
            Boundary<float, ProtectionType::TIME_ACCUMULATION> hems_1_time_protection = {&data.coil_current_hems_1,max_persistent_current,time_limit,current_read_frequency};
            Boundary<float, ProtectionType::TIME_ACCUMULATION> hems_3_time_protection = {&data.coil_current_hems_3,max_persistent_current,time_limit,current_read_frequency};
            Boundary<float, ProtectionType::TIME_ACCUMULATION> ems_1_time_protection = {&data.coil_current_ems_1,max_persistent_current,time_limit,current_read_frequency};
            Boundary<float, ProtectionType::TIME_ACCUMULATION> ems_3_time_protection = {&data.coil_current_ems_3,max_persistent_current,time_limit,current_read_frequency};

            Sensors(Data<LPU_VALIDATION>& data) : data(data) {};
            ~Sensors();

            void read_currents(){
            	current_hems_1_sensor.read();
            	current_hems_3_sensor.read();
            	current_ems_1_sensor.read();
            	current_ems_3_sensor.read();
            	hems_1_time_protection.check_accumulation(current_hems_1_sensor.);
            }

            void read_airgaps();
            void read_temps();
    };
} 
