################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/Src/stm32_adc.c \
../Drivers/Src/stm32_gpio.c \
../Drivers/Src/stm32_tim.c \
../Drivers/Src/stm32_uart.c 

OBJS += \
./Drivers/Src/stm32_adc.o \
./Drivers/Src/stm32_gpio.o \
./Drivers/Src/stm32_tim.o \
./Drivers/Src/stm32_uart.o 

C_DEPS += \
./Drivers/Src/stm32_adc.d \
./Drivers/Src/stm32_gpio.d \
./Drivers/Src/stm32_tim.d \
./Drivers/Src/stm32_uart.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/Src/%.o Drivers/Src/%.su Drivers/Src/%.cyclo: ../Drivers/Src/%.c Drivers/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DSTM32 -DSTM32F1 -DSTM32F103C6Tx -DSTM32F103x6 -c -I../Inc -I"C:/Users/nguye/STM32CubeIDE/workspace_1.17.0/SMARTOFFICE/Drivers/Inc" -I"C:/Users/nguye/STM32CubeIDE/workspace_1.17.0/SMARTOFFICE/Drivers/CMSIS/Device/ST/STM32F1xx/Include" -I"C:/Users/nguye/STM32CubeIDE/workspace_1.17.0/SMARTOFFICE/Drivers/CMSIS/Include" -I"C:/Users/nguye/STM32CubeIDE/workspace_1.17.0/SMARTOFFICE/tools/Inc" -I"C:/Users/nguye/STM32CubeIDE/workspace_1.17.0/SMARTOFFICE/Core/Inc" -I"C:/Users/nguye/STM32CubeIDE/workspace_1.17.0/SMARTOFFICE/Sevice/Inc/Com" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Drivers-2f-Src

clean-Drivers-2f-Src:
	-$(RM) ./Drivers/Src/stm32_adc.cyclo ./Drivers/Src/stm32_adc.d ./Drivers/Src/stm32_adc.o ./Drivers/Src/stm32_adc.su ./Drivers/Src/stm32_gpio.cyclo ./Drivers/Src/stm32_gpio.d ./Drivers/Src/stm32_gpio.o ./Drivers/Src/stm32_gpio.su ./Drivers/Src/stm32_tim.cyclo ./Drivers/Src/stm32_tim.d ./Drivers/Src/stm32_tim.o ./Drivers/Src/stm32_tim.su ./Drivers/Src/stm32_uart.cyclo ./Drivers/Src/stm32_uart.d ./Drivers/Src/stm32_uart.o ./Drivers/Src/stm32_uart.su

.PHONY: clean-Drivers-2f-Src

