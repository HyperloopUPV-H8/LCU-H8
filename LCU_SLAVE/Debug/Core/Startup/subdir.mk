################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
S_SRCS += \
../Core/Startup/startup_stm32h723zgtx.s 

S_DEPS += \
./Core/Startup/startup_stm32h723zgtx.d 

OBJS += \
./Core/Startup/startup_stm32h723zgtx.o 


# Each subdirectory must supply rules for building sources it contributes
Core/Startup/%.o: ../Core/Startup/%.s Core/Startup/subdir.mk
	arm-none-eabi-gcc -mcpu=cortex-m7 -g3 -DDEBUG -DDATA_IN_D2_SRAM -c -I"/home/dgoncas/Desktop/5DOF/ST-LIB" -I"/home/dgoncas/Desktop/5DOF/ST-LIB/Inc" -I"/home/dgoncas/Desktop/5DOF/ST-LIB/Inc/HALAL/Models" -I"/home/dgoncas/Desktop/5DOF/ST-LIB/Inc/HALAL/Services" -I"/home/dgoncas/Desktop/5DOF/ST-LIB/Inc/ST-LIB_LOW" -I"/home/dgoncas/Desktop/5DOF/ST-LIB/Inc/ST-LIB_HIGH" -I"/home/dgoncas/Desktop/5DOF/ST-LIB/Inc/HALAL/Services/Communication" -I"/home/dgoncas/Desktop/5DOF/ST-LIB/Inc/HALAL/Services/Communication/Ethernet" -I"/home/dgoncas/Desktop/5DOF/ST-LIB/Inc/HALAL/Services/Communication/Ethernet/UDP" -I"/home/dgoncas/Desktop/5DOF/ST-LIB/Inc/HALAL/Services/Communication/Ethernet/TCP" -x assembler-with-cpp -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@" "$<"

clean: clean-Core-2f-Startup

clean-Core-2f-Startup:
	-$(RM) ./Core/Startup/startup_stm32h723zgtx.d ./Core/Startup/startup_stm32h723zgtx.o

.PHONY: clean-Core-2f-Startup

