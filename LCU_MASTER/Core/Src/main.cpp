#include "main.h"
#include "lwip.h"

#include "ST-LIB.hpp"
#include "Runes/Runes.hpp"
#include "LCU_MASTER.hpp"
#include "LCU_Time/LCU_Time.hpp"

using namespace LCU;

int main(void)
{
	LCU_MASTER<VEHICLE_5DOF> lcu_master_singleton;
	LCU_MASTER<VEHICLE_5DOF>::lcu_master = &lcu_master_singleton;
	LCU_MASTER<VEHICLE_5DOF>::lcu_master->init();
	CyclicActions<MASTER_MODE::VEHICLE_5DOF>::register_cyclic_actions();
	while(1) {
		STLIB::update();
	}
}

void Error_Handler(void)
{
	ErrorHandler("HAL error handler triggered");
	while (1){}
}
