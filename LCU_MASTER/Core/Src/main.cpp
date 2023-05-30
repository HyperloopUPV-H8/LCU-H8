#include "main.h"
#include "lwip.h"

#include "ST-LIB.hpp"
#include "Runes/Runes.hpp"
#include "LCU_MASTER.hpp"
#include "LCU_Time/LCU_Time.hpp"

LCU::LCU_MASTER<LCU::MASTER_MODE::VEHICLE_5DOF>& lcu = LCU::LCU_MASTER<LCU::MASTER_MODE::VEHICLE_5DOF>::lcu_master;

int main(void)
{
	lcu.init();
	LCU::CyclicActions<LCU::MASTER_MODE::VEHICLE_5DOF>::register_cyclic_actions();
	while(1) {
		STLIB::update();
	}
}

void Error_Handler(void)
{
	ErrorHandler("HAL error handler triggered");
	while (1){}
}
