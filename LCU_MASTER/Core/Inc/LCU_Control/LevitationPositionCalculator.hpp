#pragma once

#include "Control/ControlBlock.hpp"
#include "math.h"
#include "LevitationPosition.hpp"

class LevitationPositionCalculator : public ControlBlock<float(*)[8], LevitationPosition>{
public:
    static constexpr double x_sragy = 768.1, y_sragy = 95.1, z_sragy = 79.22;
    static constexpr double x_sragz = 767.85, y_sragz = 222.69, z_sragz = -94.93;
    static constexpr double z_infr = 632.8;
    static constexpr double grosorz = 15, grosory = 5;

    float(&distances)[8] = *this->input_value;

    LevitationPositionCalculator(float(&distances)[8]){
        this->input_value = &distances;
        output_value = {0.0,0.0,0.0,0.0,0.0};
    };
    void execute() override{
        float rotation_x_temp = (asin((distances[1] - distances[0])/(2*y_sragz)) + asin((distances[3] - distances[2])/(2*y_sragz)))/2.0;
        float rotation_y_temp = (asin((distances[0] - distances[2])/(2*x_sragz)) + asin((distances[1] - distances[3])/(2*x_sragz)))/2.0;
        float rotation_z_temp = (asin((distances[4] - distances[6])/(2*x_sragy)) + asin((distances[7] - distances[5])/(2*x_sragy)))/2.0;

        float y_temp =  (distances[4] - y_sragy*cos(output_value.rotation_z) - x_sragy*sin(output_value.rotation_z) + z_sragy*sin(output_value.rotation_x) + grosory)/4.0;
        y_temp +=  ((-1*distances[5]) + y_sragy*cos(output_value.rotation_z) - x_sragy*sin(output_value.rotation_z) + z_sragy*sin(output_value.rotation_x) - grosory)/4.0;
        y_temp += (distances[6] - y_sragy*cos(output_value.rotation_z) + x_sragy*sin(output_value.rotation_z) + z_sragy*sin(output_value.rotation_x) + grosory)/4.0;
        y_temp += ((-1*distances[7]) + y_sragy*cos(output_value.rotation_z) + x_sragy*sin(output_value.rotation_z) + z_sragy*sin(output_value.rotation_x) - grosory)/4.0;

        float z_temp = (z_infr - distances[0] - z_sragz*cos(output_value.rotation_y) + x_sragz*sin(output_value.rotation_y) - y_sragz*sin(output_value.rotation_x))/4.0;
        z_temp += (z_infr - distances[1] - z_sragz*cos(output_value.rotation_y) + x_sragz*sin(output_value.rotation_y) + y_sragz*sin(output_value.rotation_x))/4.0;
        z_temp +=  (z_infr - distances[2] - z_sragz*cos(output_value.rotation_y) - x_sragz*sin(output_value.rotation_y) - y_sragz*sin(output_value.rotation_x))/4.0;
        z_temp += (z_infr - distances[3] - z_sragz*cos(output_value.rotation_y) - x_sragz*sin(output_value.rotation_y) + y_sragz*sin(output_value.rotation_x))/4.0;

        HAL_NVIC_DisableIRQ(TIM7_IRQn);
        output_value.rotation_x = rotation_x_temp;
        output_value.rotation_y = rotation_y_temp;
        output_value.rotation_z = rotation_z_temp;
        output_value.y = y_temp;
        output_value.z = z_temp;
        HAL_NVIC_EnableIRQ(TIM7_IRQn);
    }

    void reset_position(){
        output_value = {0.0,0.0,0.0,0.0,0.0};
    }
};
