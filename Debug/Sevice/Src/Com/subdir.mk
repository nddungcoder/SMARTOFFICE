################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Sevice/Src/Com/fsm_message.c \
../Sevice/Src/Com/uart.c 

OBJS += \
./Sevice/Src/Com/fsm_message.o \
./Sevice/Src/Com/uart.o 

C_DEPS += \
./Sevice/Src/Com/fsm_message.d \
./Sevice/Src/Com/uart.d 


# Each subdirectory must supply rules for building sources it contributes
Sevice/Src/Com/%.o Sevice/Src/Com/%.su Sevice/Src/Com/%.cyclo: ../Sevice/Src/Com/%.c Sevice/Src/Com/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DSTM32 -DSTM32F1 -DSTM32F103C6Tx -DSTM32F103x6 -c -I"C:/Users/nguye/STM32CubeIDE/workspace_1.17.0/SMARTOFFICE/Drivers/Inc" -I"C:/Users/nguye/STM32CubeIDE/workspace_1.17.0/SMARTOFFICE/Drivers/CMSIS/Device/ST/STM32F1xx/Include" -I"C:/Users/nguye/STM32CubeIDE/workspace_1.17.0/SMARTOFFICE/Drivers/CMSIS/Include" -I"C:/Users/nguye/STM32CubeIDE/workspace_1.17.0/SMARTOFFICE/tools/Inc" -I"C:/Users/nguye/STM32CubeIDE/workspace_1.17.0/SMARTOFFICE/Sevice/Inc/Com" -I"C:/Users/nguye/STM32CubeIDE/workspace_1.17.0/SMARTOFFICE/Sevice/Inc/Input" -I"C:/Users/nguye/STM32CubeIDE/workspace_1.17.0/SMARTOFFICE/Sevice/Inc/Output" -I"C:/Users/nguye/STM32CubeIDE/workspace_1.17.0/SMARTOFFICE/Sevice/Inc" -I"C:/Users/nguye/STM32CubeIDE/workspace_1.17.0/SMARTOFFICE/App/Inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Sevice-2f-Src-2f-Com

clean-Sevice-2f-Src-2f-Com:
	-$(RM) ./Sevice/Src/Com/fsm_message.cyclo ./Sevice/Src/Com/fsm_message.d ./Sevice/Src/Com/fsm_message.o ./Sevice/Src/Com/fsm_message.su ./Sevice/Src/Com/uart.cyclo ./Sevice/Src/Com/uart.d ./Sevice/Src/Com/uart.o ./Sevice/Src/Com/uart.su

.PHONY: clean-Sevice-2f-Src-2f-Com

