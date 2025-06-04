################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Sevice/Src/device_manager.c \
../Sevice/Src/interrupts.c 

OBJS += \
./Sevice/Src/device_manager.o \
./Sevice/Src/interrupts.o 

C_DEPS += \
./Sevice/Src/device_manager.d \
./Sevice/Src/interrupts.d 


# Each subdirectory must supply rules for building sources it contributes
Sevice/Src/%.o Sevice/Src/%.su Sevice/Src/%.cyclo: ../Sevice/Src/%.c Sevice/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DSTM32 -DSTM32F1 -DSTM32F103C6Tx -DSTM32F103x6 -c -I"C:/Users/nguye/STM32CubeIDE/workspace_1.17.0/SMARTOFFICE/Drivers/Inc" -I"C:/Users/nguye/STM32CubeIDE/workspace_1.17.0/SMARTOFFICE/Drivers/CMSIS/Device/ST/STM32F1xx/Include" -I"C:/Users/nguye/STM32CubeIDE/workspace_1.17.0/SMARTOFFICE/Drivers/CMSIS/Include" -I"C:/Users/nguye/STM32CubeIDE/workspace_1.17.0/SMARTOFFICE/tools/Inc" -I"C:/Users/nguye/STM32CubeIDE/workspace_1.17.0/SMARTOFFICE/Sevice/Inc/Com" -I"C:/Users/nguye/STM32CubeIDE/workspace_1.17.0/SMARTOFFICE/Sevice/Inc/Input" -I"C:/Users/nguye/STM32CubeIDE/workspace_1.17.0/SMARTOFFICE/Sevice/Inc/Output" -I"C:/Users/nguye/STM32CubeIDE/workspace_1.17.0/SMARTOFFICE/Sevice/Inc" -I"C:/Users/nguye/STM32CubeIDE/workspace_1.17.0/SMARTOFFICE/App/Inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Sevice-2f-Src

clean-Sevice-2f-Src:
	-$(RM) ./Sevice/Src/device_manager.cyclo ./Sevice/Src/device_manager.d ./Sevice/Src/device_manager.o ./Sevice/Src/device_manager.su ./Sevice/Src/interrupts.cyclo ./Sevice/Src/interrupts.d ./Sevice/Src/interrupts.o ./Sevice/Src/interrupts.su

.PHONY: clean-Sevice-2f-Src

