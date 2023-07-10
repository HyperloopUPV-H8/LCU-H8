#pragma once

namespace LCU{

	enum COIL_ID {
		HEMS_1,
		HEMS_2,
		HEMS_3,
		HEMS_4,
		EMS_1,
		EMS_2,
		EMS_3,
		EMS_4
	};

	inline COIL_ID operator++ (COIL_ID& id, int) {
	    id = static_cast<COIL_ID>(static_cast<int>(id) + 1);
	    return id;
	}

    enum MASTER_MODE{
    LPU_VALIDATION,
    TESTBENCH_1DOF,
    VEHICLE_TESTING,
    VEHICLE_5DOF,
};

}