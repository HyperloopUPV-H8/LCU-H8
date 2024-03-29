#pragma once
#include "IPV4/IPV4.hpp"

namespace LCU{
    const IPV4 SLAVE_IP = {"192.168.1.5"};
    const IPV4 MASTER_IP = {"192.168.1.4"};
    const IPV4 BACKEND_IP = {"192.168.0.9"};
    constexpr uint16_t SERVER_PORT = 50500;
    constexpr uint16_t CLIENT_PORT = 50501;
    constexpr uint16_t UDP_PORT = 50400;

    namespace Pinout{
        // PWMs
        constexpr Pin& HEMS1_H1_PIN = PE9; // <-
        constexpr Pin& HEMS1_H2_PIN = PE6;
        constexpr Pin& EMS1_H1_PIN = PE13; // <-
        constexpr Pin& EMS1_H2_PIN = PE14;

        constexpr Pin& HEMS3_H1_PIN = PE11; // <-
        constexpr Pin& HEMS3_H2_PIN = PE5;
        constexpr Pin& EMS3_H1_PIN = PB4;
        constexpr Pin& EMS3_H2_PIN = PB5;

        //LEDs
        constexpr Pin& SLEEP_LED_PIN = PG4;
        constexpr Pin& FLASH_LED_PIN = PG5;
        constexpr Pin& CAN_LED_PIN = PG6;
        constexpr Pin& FAULT_LED_PIN = PG7;
        constexpr Pin& OPERATIONAL_LED_PIN = PG8;

        //Digital Outputs
        constexpr Pin& BUFFER_EN_PIN = PD14;

        //Digital Inputs
        constexpr Pin& LPU_DCDC_GOOD_PIN = PD15;

        //ADCs
        constexpr Pin& HEMS1_CURRENT_PIN = PF11;
        constexpr Pin& HEMS3_CURRENT_PIN = PB1;
        constexpr Pin& EMS1_CURRENT_PIN = PB0;
        constexpr Pin& EMS3_CURRENT_PIN = PF12;

        constexpr Pin& HEMS1_TEMP_PIN = PF5;
        constexpr Pin& HEMS3_TEMP_PIN = PF7;
        constexpr Pin& EMS1_TEMP_PIN = PF6;
        constexpr Pin& EMS3_TEMP_PIN = PF8;

        constexpr Pin& AIRGAP_1_PIN = PA6;
        constexpr Pin& AIRGAP_3_PIN = PA4;
        constexpr Pin& AIRGAP_5_PIN = PA3;
        constexpr Pin& AIRGAP_7_PIN = PA5;

        constexpr Pin& BATT_VOLTAGE_LPU_1_PIN = PA0;
        constexpr Pin& BATT_VOLTAGE_LPU_2_PIN = PF14;

        constexpr Pin& LPU_1_TEMP_1_PIN = PC2;
        constexpr Pin& LPU_1_TEMP_2_PIN = PC3;
        constexpr Pin& LPU_2_TEMP_1_PIN = PF9;
        constexpr Pin& LPU_2_TEMP_2_PIN = PF10;
    }
}
