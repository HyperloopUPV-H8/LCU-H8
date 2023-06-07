#pragma once

#include "Control/ControlBlock.hpp"
#include "math.h"
#include "LevitationPosition.hpp"

class LevitationPositionCalculator : public ControlBlock<float(*)[8], LevitationPosition>{
public:
    static constexpr double x_sragy = 0.7681, y_sragy = 0.0951, z_sragy = 0.07922;
    static constexpr double x_sragz = 0.76785, y_sragz = 0.22269, z_sragz = -0.09493;
    static constexpr double z_infr = 0.6328;
    static constexpr double grosorz = 0.015, grosory = 0.005;

    float(&distances)[8] = *this->input_value;

    LevitationPositionCalculator(float(&distances)[8]){
        this->input_value = &distances;
        output_value = {0.0,0.0,0.0,0.0,0.0};
    };
    void execute() override{
        reset_position();
        output_value.rotation_x = (asin((distances[1] - distances[0])/(2*y_sragz)) + asin((distances[3] - distances[2])/(2*y_sragz)))/2.0;
        output_value.rotation_y = (asin((distances[0] - distances[2])/(2*x_sragz)) + asin((distances[1] - distances[3])/(2*x_sragz)))/2.0;
        output_value.rotation_z = (asin((distances[4] - distances[6])/(2*x_sragy)) + asin((distances[7] - distances[5])/(2*x_sragy)))/2.0;

        output_value.y += (distances[4] - y_sragy*cos(output_value.rotation_z) - x_sragy*sin(output_value.rotation_z) + y_sragz*sin(output_value.rotation_x))/4.0;
        output_value.y += ((-1*distances[5]) + y_sragy*cos(output_value.rotation_z) - x_sragy*sin(output_value.rotation_z) + y_sragz*sin(output_value.rotation_x))/4.0;
        output_value.y += (distances[6] - y_sragy*cos(output_value.rotation_z) + x_sragy*sin(output_value.rotation_z) + y_sragz*sin(output_value.rotation_x))/4.0;
        output_value.y += ((-1*distances[7]) + y_sragy*cos(output_value.rotation_z) + x_sragy*sin(output_value.rotation_z) + y_sragz*sin(output_value.rotation_x))/4.0;

        output_value.z += (z_infr - distances[0] - z_sragz*cos(output_value.rotation_y) + x_sragz*sin(output_value.rotation_y) - y_sragz*sin(output_value.rotation_x))/4.0;
        output_value.z += (z_infr - distances[1] - z_sragz*cos(output_value.rotation_y) + x_sragz*sin(output_value.rotation_y) + y_sragz*sin(output_value.rotation_x))/4.0;
        output_value.z += (z_infr - distances[2] - z_sragz*cos(output_value.rotation_y) - x_sragz*sin(output_value.rotation_y) - y_sragz*sin(output_value.rotation_x))/4.0;
        output_value.z += (z_infr - distances[3] - z_sragz*cos(output_value.rotation_y) - x_sragz*sin(output_value.rotation_y) + y_sragz*sin(output_value.rotation_x))/4.0;
    }

    void reset_position(){
        output_value = {0.0,0.0,0.0,0.0,0.0};
    }
};
