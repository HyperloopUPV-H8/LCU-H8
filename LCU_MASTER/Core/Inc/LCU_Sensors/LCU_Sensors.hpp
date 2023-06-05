#pragma once
#include "LCU_Mode/LCU_Mode.hpp"
#include "LCU_Data/LCU_Data.hpp"
#include "LCU_Pinout/Pinout.hpp"
#include "Control/Blocks/MovingAverage.hpp"
#include "Sensors/LinearSensor/FilteredLinearSensor.hpp"
#include "Protections/Boundary.hpp"
namespace LCU{
    template<LCU::MASTER_MODE> class Sensors;

    template<> class Sensors<MASTER_MODE::LPU_VALIDATION>{
        public:
            Data<LPU_VALIDATION>& data;
            // Airgaps
            static constexpr float airgap_slope = 17.23477;
            static constexpr float airgap_offset = 50.45231;
            static constexpr float offset_mecanico = 63.303;
            static constexpr size_t aigarp_filter_order = 10;
            MovingAverage<aigarp_filter_order> airgap_1_filter;
            MovingAverage<aigarp_filter_order> airgap_3_filter;
            MovingAverage<aigarp_filter_order> airgap_5_filter;
            MovingAverage<aigarp_filter_order> airgap_7_filter;
            FilteredLinearSensor<float,aigarp_filter_order> airgap_1_sensor {Pinout::AIRGAP_1_PIN, airgap_slope, airgap_offset - offset_mecanico, data.airgaps[1-1], airgap_1_filter};
            FilteredLinearSensor<float,aigarp_filter_order> airgap_3_sensor {Pinout::AIRGAP_3_PIN, airgap_slope, airgap_offset - offset_mecanico, data.airgaps[3-1], airgap_3_filter};
            FilteredLinearSensor<float,aigarp_filter_order> airgap_5_sensor {Pinout::AIRGAP_5_PIN, airgap_slope, airgap_offset - offset_mecanico, data.airgaps[5-1], airgap_5_filter};
            FilteredLinearSensor<float,aigarp_filter_order> airgap_7_sensor {Pinout::AIRGAP_7_PIN, airgap_slope, airgap_offset - offset_mecanico, data.airgaps[7-1], airgap_7_filter};

            // Curents
            static constexpr float current_slope = 44.746;
            static constexpr float current_offset = -85.72;

            static constexpr size_t current_filter_order = 20;
            MovingAverage<current_filter_order> current_hems_1_filter;
            MovingAverage<current_filter_order> current_hems_3_filter;
            MovingAverage<current_filter_order> current_ems_1_filter;
            MovingAverage<current_filter_order> current_ems_3_filter;
            FilteredLinearSensor<float,current_filter_order> current_hems_1_sensor {Pinout::HEMS1_CURRENT_PIN, current_slope, current_offset, data.coil_current_hems_1 ,current_hems_1_filter};
            FilteredLinearSensor<float,current_filter_order> current_hems_3_sensor {Pinout::HEMS3_CURRENT_PIN, current_slope, current_offset, data.coil_current_hems_3, current_hems_3_filter};
            FilteredLinearSensor<float,current_filter_order> current_ems_1_sensor {Pinout::EMS1_CURRENT_PIN, current_slope, current_offset, data.coil_current_ems_1, current_ems_1_filter};
            FilteredLinearSensor<float,current_filter_order> current_ems_3_sensor {Pinout::EMS3_CURRENT_PIN, current_slope, current_offset, data.coil_current_ems_3, current_ems_3_filter};

//			  Temparatures
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

            Sensors(Data<LPU_VALIDATION>& data) : data(data) {};

            void read_currents(){
            	current_hems_1_sensor.read();
            	current_hems_3_sensor.read();
            	current_ems_1_sensor.read();
            	current_ems_3_sensor.read();
            }

            void read_airgaps(){
            	airgap_1_sensor.read();
            	airgap_3_sensor.read();
            	airgap_5_sensor.read();
            	airgap_7_sensor.read();
            }

//            void read_temps(){
//            	hems_1_temperature_sensor.read();
//            	hems_3_temperature_sensor.read();
//            	ems_1_temperature_sensor.read();
//            	ems_3_temperature_sensor.read();
//            }
    };

    template<> class Sensors<MASTER_MODE::TESTBENCH_1DOF>{
    public:
    	Data<TESTBENCH_1DOF>& data;
    	//Airgap
        static constexpr float airgap_slope = 17.23477;
        static constexpr float airgap_offset = 50.45231;
        static constexpr float offset_mecanico = 63.303;
        static constexpr size_t aigarp_filter_order = 10;
        static constexpr Pin& airgap_pin = Pinout::AIRGAP_1_PIN;
        MovingAverage<aigarp_filter_order> airgap_filter;
        FilteredLinearSensor<float,aigarp_filter_order> airgap_sensor {airgap_pin, airgap_slope, airgap_offset - offset_mecanico, data.airgap, airgap_filter};

        //Current
        static constexpr float current_slope = 44.746;
        static constexpr float current_offset = -85.72;

        static constexpr size_t current_filter_order = 20;
        static constexpr Pin& current_pin = Pinout::HEMS1_CURRENT_PIN;
        MovingAverage<current_filter_order> current_filter;
        FilteredLinearSensor<float,current_filter_order> current_sensor {current_pin, current_slope, current_offset, data.coil_current, current_filter};

        //Tmperature
//        static constexpr float temperature_slope;
//        static constexpr float temperature_offset;
//
//        static constexpr size_t temperature_filter_order = 10;
//        static constexpr Pin& temperature_pin = Pinout::HEMS1_TEMP_PIN;
//        MovingAverage<temperature_filter_order> temperature_filter;
//        FilteredLinearSensor<temperature_filter_order> temperature_sensor {temperature_pin, temperature_slope, temperature_offset, data.coil_temp, temperature_filter};

        Sensors(Data<TESTBENCH_1DOF>& data) : data(data){}

        void read_currents(){
        	current_sensor.read();
        	hems_1_time_protection->check_accumulation(data.coil_current);
        }

        void read_airgaps(){
        	airgap_sensor.read();
        }

//        void read_temps(){
//        	temperature_sensor.read();
//        }
    };

    template<> class Sensors<MASTER_MODE::VEHICLE_5DOF>{
        public:
            Data<VEHICLE_5DOF>& data;
            // Airgaps
            static constexpr float airgap_slope = 17.23477;
            static constexpr float airgap_offset = 50.45231;
            static constexpr float offset_mecanico = 63.303;
            static constexpr size_t aigarp_filter_order = 10;
            MovingAverage<aigarp_filter_order> airgap_1_filter;
            MovingAverage<aigarp_filter_order> airgap_3_filter;
            MovingAverage<aigarp_filter_order> airgap_5_filter;
            MovingAverage<aigarp_filter_order> airgap_7_filter;
            FilteredLinearSensor<float,aigarp_filter_order> airgap_1_sensor {Pinout::AIRGAP_1_PIN, airgap_slope, airgap_offset - offset_mecanico, data.airgaps[1-1], airgap_1_filter};
            FilteredLinearSensor<float,aigarp_filter_order> airgap_3_sensor {Pinout::AIRGAP_3_PIN, airgap_slope, airgap_offset - offset_mecanico, data.airgaps[3-1], airgap_3_filter};
            FilteredLinearSensor<float,aigarp_filter_order> airgap_5_sensor {Pinout::AIRGAP_5_PIN, airgap_slope, airgap_offset - offset_mecanico, data.airgaps[5-1], airgap_5_filter};
            FilteredLinearSensor<float,aigarp_filter_order> airgap_7_sensor {Pinout::AIRGAP_7_PIN, airgap_slope, airgap_offset - offset_mecanico, data.airgaps[7-1], airgap_7_filter};

            // Curents
            static constexpr float current_slope = 44.746;
            static constexpr float current_offset = -85.72;

            static constexpr size_t current_filter_order = 20;
            MovingAverage<current_filter_order> current_hems_1_filter;
            MovingAverage<current_filter_order> current_hems_3_filter;
            MovingAverage<current_filter_order> current_ems_1_filter;
            MovingAverage<current_filter_order> current_ems_3_filter;
            FilteredLinearSensor<float,current_filter_order> current_hems_1_sensor {Pinout::HEMS1_CURRENT_PIN, current_slope, current_offset, data.coil_current_hems_1 ,current_hems_1_filter};
            FilteredLinearSensor<float,current_filter_order> current_hems_3_sensor {Pinout::HEMS3_CURRENT_PIN, current_slope, current_offset, data.coil_current_hems_3, current_hems_3_filter};
            FilteredLinearSensor<float,current_filter_order> current_ems_1_sensor {Pinout::EMS1_CURRENT_PIN, current_slope, current_offset, data.coil_current_ems_1, current_ems_1_filter};
            FilteredLinearSensor<float,current_filter_order> current_ems_3_sensor {Pinout::EMS3_CURRENT_PIN, current_slope, current_offset, data.coil_current_ems_3, current_ems_3_filter};

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

            Sensors(Data<VEHICLE_5DOF>& data) : data(data) {};

            void read_currents(){
            	current_hems_1_sensor.read();
            	current_hems_3_sensor.read();
            	current_ems_1_sensor.read();
            	current_ems_3_sensor.read();
            	//hems_1_time_protection->check_accumulation(data.coil_current_hems_1);
            	//hems_3_time_protection->check_accumulation(data.coil_current_hems_3);
            }

            void read_airgaps(){
            	airgap_1_sensor.read();
            	airgap_3_sensor.read();
            	airgap_5_sensor.read();
            	airgap_7_sensor.read();
            }

//            void read_temps(){
//            	hems_1_temperature_sensor.read();
//            	hems_3_temperature_sensor.read();
//            	ems_1_temperature_sensor.read();
//            	ems_3_temperature_sensor.read();
//            }
    };

    template<> class Sensors<MASTER_MODE::VEHICLE_TESTING>{
            public:
                Data<VEHICLE_TESTING>& data;
                // Airgaps
                static constexpr float airgap_slope = 17.23477;
                static constexpr float airgap_offset = 50.45231;
                static constexpr float offset_mecanico = 63.303;
                static constexpr size_t aigarp_filter_order = 10;
                MovingAverage<aigarp_filter_order> airgap_1_filter;
                MovingAverage<aigarp_filter_order> airgap_3_filter;
                MovingAverage<aigarp_filter_order> airgap_5_filter;
                MovingAverage<aigarp_filter_order> airgap_7_filter;
                FilteredLinearSensor<float,aigarp_filter_order> airgap_1_sensor {Pinout::AIRGAP_1_PIN, airgap_slope, airgap_offset - offset_mecanico, data.airgaps[1-1], airgap_1_filter};
                FilteredLinearSensor<float,aigarp_filter_order> airgap_3_sensor {Pinout::AIRGAP_3_PIN, airgap_slope, airgap_offset - offset_mecanico, data.airgaps[3-1], airgap_3_filter};
                FilteredLinearSensor<float,aigarp_filter_order> airgap_5_sensor {Pinout::AIRGAP_5_PIN, airgap_slope, airgap_offset - offset_mecanico, data.airgaps[5-1], airgap_5_filter};
                FilteredLinearSensor<float,aigarp_filter_order> airgap_7_sensor {Pinout::AIRGAP_7_PIN, airgap_slope, airgap_offset - offset_mecanico, data.airgaps[7-1], airgap_7_filter};

                // Curents
                static constexpr float current_slope = 44.746;
                static constexpr float current_offset = -85.72;

                static constexpr size_t current_filter_order = 20;
                MovingAverage<current_filter_order> current_hems_1_filter;
                MovingAverage<current_filter_order> current_hems_3_filter;
                MovingAverage<current_filter_order> current_ems_1_filter;
                MovingAverage<current_filter_order> current_ems_3_filter;
                FilteredLinearSensor<float,current_filter_order> current_hems_1_sensor {Pinout::HEMS1_CURRENT_PIN, current_slope, current_offset, data.coil_current_hems_1 ,current_hems_1_filter};
                FilteredLinearSensor<float,current_filter_order> current_hems_3_sensor {Pinout::HEMS3_CURRENT_PIN, current_slope, current_offset, data.coil_current_hems_3, current_hems_3_filter};
                FilteredLinearSensor<float,current_filter_order> current_ems_1_sensor {Pinout::EMS1_CURRENT_PIN, current_slope, current_offset, data.coil_current_ems_1, current_ems_1_filter};
                FilteredLinearSensor<float,current_filter_order> current_ems_3_sensor {Pinout::EMS3_CURRENT_PIN, current_slope, current_offset, data.coil_current_ems_3, current_ems_3_filter};

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

                Sensors(Data<VEHICLE_TESTING>& data) : data(data) {};

                void read_currents(){
                	current_hems_1_sensor.read();
                	current_hems_3_sensor.read();
                	current_ems_1_sensor.read();
                	current_ems_3_sensor.read();
                	//hems_1_time_protection->check_accumulation(data.coil_current_hems_1);
                	//hems_3_time_protection->check_accumulation(data.coil_current_hems_3);
                }

                void read_airgaps(){
                	airgap_1_sensor.read();
                	airgap_3_sensor.read();
                	airgap_5_sensor.read();
                	airgap_7_sensor.read();
                }

    //            void read_temps(){
    //            	hems_1_temperature_sensor.read();
    //            	hems_3_temperature_sensor.read();
    //            	ems_1_temperature_sensor.read();
    //            	ems_3_temperature_sensor.read();
    //            }
        };
} 
