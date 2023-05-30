#pragma once
#include "LCU_Mode/LCU_Mode.hpp"
#include "Control/Blocks/PID.hpp"
#include "Control/Blocks/Saturator.hpp"
#include "LevitationPositionCalculator.hpp"
#include "Control/Blocks/MovingAverage.hpp"
#include "Control/Blocks/MatrixMultiplier.hpp"

template<LCU::MASTER_MODE> class DistanceControl;

template<>
class DistanceControl<LCU::MASTER_MODE::LPU_VALIDATION>{
};

template<>
class DistanceControl<LCU::MASTER_MODE::TESTBENCH_1DOF>{
public:
	PID<IntegratorType::Trapezoidal,FilterDerivatorType::Moving_Average,22> pid = {ki,kp,kp,period};
	Saturator<float> target_current_saturator = Saturator((float)0.0,(float)-50.0,(float)50.0);
	float reference_distance = 0.0199;
	float target_current = 0.0;
	static constexpr float ki = -7000, kp = -1400, kd = -475, period = 0.001;
	DistanceControl() = default;
	void set_reference_distance(float new_distance){
		reference_distance = new_distance;
	}
	void control(float real_distance){
		pid.input(reference_distance - real_distance/1000.0);
		pid.execute();
		target_current_saturator.input(pid.output_value);
		target_current_saturator.execute();
		target_current = target_current_saturator.output_value;
	}

	void reset(){
		pid.reset();
		target_current = 0.0;
	}
};

template<>
class DistanceControl<LCU::MASTER_MODE::VEHICLE_5DOF>{
public:
	SimpleDerivator y_derivator, z_derivator, rot_y_derivator, rot_z_derivator, rot_x_derivator;
	Integrator<IntegratorType::Trapezoidal> y_integrator, z_integrator, rot_y_integrator, rot_z_integrator, rot_x_integrator;
	MovingAverage<20> y_filter_derivative, z_filter_derivative, rot_y_filter_derivative, rot_z_filter_derivative, rot_x_filter_derivative;
	LevitationPosition error;
	LevitationPositionCalculator airgap2pos;
	LevitationPosition& levitation_position = airgap2pos.output_value;

	const double default_z_reference = 0.61448;
	double z_reference = default_z_reference;

	static constexpr float period = 0.001;

	float(&current_references)[8];

    double K[8][15] = {
        {0,                    -6714.20156538224, -2103.82345823758, 5636.21746716481,  0,                 0,                 -139.384227675325, -138.410088630474, 369.397530125506,  0,                 0,                 -1155.63188429707, -1529.05575562367, 1514.51071219874,  0},
        {0,                    -6714.20156538224, 2103.82345823758,  5636.21746716481,  0,                 0,                 -139.384227675325, 138.410088630474,  369.397530125506,  0,                 0,                 -1155.63188429707, 1529.05575562367,  1514.51071219874,  0},
        {0,                    -6714.20156538224, -2103.82345823758, -5636.21746716481, 0,                 0,                 -139.384227675325, -138.410088630474, -369.397530125506, 0,                 0,                 -1155.63188429707, -1529.05575562367, -1514.51071219874, 0},
        {0,                    -6714.20156538224, 2103.82345823758,  -5636.21746716481, 0,                 0,                 -139.384227675325, 138.410088630474,  -369.397530125506, 0,                 0,                 -1155.63188429707, 1529.05575562367,  -1514.51071219874, 0},
        {6002.75566687231,     0,                 0,                 0,                 2377.67828276700,  627.222912438565,  0,                 0,                 0,                 239.418374409612,  538.479508989030,  0,                 0,                 0,                 1851.90394960322},
        {-6002.75566687231,    0,                 0,                 0,                 -2377.67828276700, -627.222912438565, 0,                 0,                 0,                 -239.418374409612, -538.479508989030, 0,                 0,                 0,                 -1851.90394960322},
        {6002.75566687231,     0,                 0,                 0,                 -2377.67828276700, 627.222912438565,  0,                 0,                 0,                 -239.418374409612, 538.479508989030,  0,                 0,                 0,                 -1851.90394960322},
        {-6002.75566687231,    0,                 0,                 0,                 2377.67828276700,  -627.222912438565, 0,                 0,                 0,                 239.418374409612, -538.479508989030,  0,                 0,                 0,                 1851.90394960322}
    };


	double U[15];

	MatrixMultiplier<8,15,1> matrix_multiplier;

	DistanceControl(float(&distaces)[8], float(&current_references)[8]) : y_integrator(period,1), z_integrator(period,1),
		rot_x_integrator(period,1), rot_y_integrator(period,1), rot_z_integrator(period,1),
		y_derivator(period), z_derivator(period), rot_x_derivator(period), rot_y_derivator(period), rot_z_derivator(period),
		matrix_multiplier(K,U,current_references), airgap2pos(distaces), current_references(current_references)
	{}
private:

	enum U_MATRIX_POSITION{
		POS_Y,
		POS_Z,
		ROT_X,
		ROT_Y,
		ROT_Z,
		dPOS_Y,
		dPOS_Z,
		dROT_X,
		dROT_Y,
		dROT_Z,
		iPOS_Y,
		iPOS_Z,
		iROT_X,
		iROT_Y,
		iROT_Z
	};

	void calculate_error(){
		error = levitation_position;
		error.z = z_reference - levitation_position.z;
	}

	void store_u(){
		U[POS_Y] = error.y;
		U[POS_Z] = error.z;
		U[ROT_X] = error.rotation_x;
		U[ROT_Y] = error.rotation_y;
		U[ROT_Z] = error.rotation_z;
		U[dPOS_Y] = y_filter_derivative.output_value;
		U[dPOS_Z] = z_filter_derivative.output_value;
		U[dROT_X] = rot_x_filter_derivative.output_value;
		U[dROT_Y] = rot_y_filter_derivative.output_value;
		U[dROT_Z] = rot_z_filter_derivative.output_value;
		U[iPOS_Y] = y_integrator.output_value;
		U[iPOS_Z] = z_integrator.output_value;
		U[iROT_X] = rot_x_integrator.output_value;
		U[iROT_Y] = rot_y_integrator.output_value;
		U[iROT_Z] = rot_z_integrator.output_value;
	}

public:
	void control(){
		airgap2pos.execute();
		calculate_error();

		//Derivative
		y_derivator.input(error.y);
		z_derivator.input(error.z);
		rot_x_derivator.input(error.rotation_x);
		rot_y_derivator.input(error.rotation_y);
		rot_z_derivator.input(error.rotation_z);
		y_derivator.execute();
		z_derivator.execute();
		rot_y_derivator.execute();
		rot_x_derivator.execute();
		rot_z_derivator.execute();
		y_filter_derivative.input(y_derivator.output_value);
		z_filter_derivative.input(z_derivator.output_value);
		rot_x_filter_derivative.input(rot_x_derivator.output_value);
		rot_y_filter_derivative.input(rot_y_derivator.output_value);
		rot_z_filter_derivative.input(rot_z_derivator.output_value);
		y_filter_derivative.execute();
		z_filter_derivative.execute();
		rot_x_filter_derivative.execute();
		rot_y_filter_derivative.execute();
		rot_z_filter_derivative.execute();

		//Integral
		y_integrator.input(error.y);
		z_integrator.input(error.z);
		rot_x_integrator.input(error.rotation_x);
		rot_y_integrator.input(error.rotation_y);
		rot_z_integrator.input(error.rotation_z);
		y_integrator.execute();
		z_integrator.execute();
		rot_x_integrator.execute();
		rot_y_integrator.execute();
		rot_z_integrator.execute();

		store_u();
		matrix_multiplier.execute();
	}

	void set_z_reference(float new_reference){
		z_reference = new_reference;
	}

	void reset(){
		y_integrator.reset();
		z_integrator.reset();
		rot_x_integrator.reset();
		rot_y_integrator.reset();
		rot_z_integrator.reset();

		y_derivator.reset();
		z_derivator.reset();
		rot_x_derivator.reset();
		rot_y_derivator.reset();
		rot_z_derivator.reset();

		y_filter_derivative.reset();
		z_filter_derivative.reset();
		rot_x_filter_derivative.reset();
		rot_y_filter_derivative.reset();
		rot_z_filter_derivative.reset();

		matrix_multiplier.reset();

		for(double& e: U){
			e = 0.0;
		}

		levitation_position.y = 0.0;
		levitation_position.z = 0.0;
		levitation_position.rotation_x = 0.0;
		levitation_position.rotation_y = 0.0;
		levitation_position.rotation_z = 0.0;

		error.y = 0.0;
		error.z = 0.0;
		error.rotation_x = 0.0;
		error.rotation_y = 0.0;
		error.rotation_z = 0.0;

		for(float& e : current_references){
			e = 0.0;
		}

		set_z_reference(default_z_reference);
	}
};
