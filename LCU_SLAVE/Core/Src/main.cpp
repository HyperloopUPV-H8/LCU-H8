#include "main.h"
#include "lwip.h"

#include "ST-LIB.hpp"
#include "Runes/Runes.hpp"
#include "LCU_SLAVE.hpp"
#include "LCU_Time/LCU_Time.hpp"

LCU::LCU_SLAVE& lcu = LCU::LCU_SLAVE::lcu_slave;

int main(void)
{
	lcu.init();
	LCU::CyclicActions::register_cyclic_actions();
	while(1) {
		STLIB::update();
	}
}

void Error_Handler(void)
{
	ErrorHandler("HAL error handler triggered");
	while (1){}
}
