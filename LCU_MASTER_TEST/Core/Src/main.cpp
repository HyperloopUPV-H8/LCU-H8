#include "main.h"
#include "lwip.h"

#include "ST-LIB.hpp"
#include "Runes/Runes.hpp"
#include "LCU_MASTER.hpp"
#include "LCU_Time/LCU_Time.hpp"

using namespace LCU;

constexpr LCU::MASTER_MODE MODE_OF_OPERATION = VEHICLE_5DOF;

int main(void)
{
	LCU_MASTER<MODE_OF_OPERATION> lcu_master_singleton;
	LCU_MASTER<MODE_OF_OPERATION>::lcu_master = &lcu_master_singleton;
	LCU_MASTER<MODE_OF_OPERATION>::lcu_master->init();
	CyclicActions<MODE_OF_OPERATION>::register_cyclic_actions();
	while(1) {
		STLIB::update();
	}
}

void Error_Handler(void)
{
	ErrorHandler("HAL error handler triggered");
	while (1){}
}
