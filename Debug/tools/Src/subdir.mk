################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../tools/Src/convert.c \
../tools/Src/queue.c \
../tools/Src/timer_base.c 

OBJS += \
./tools/Src/convert.o \
./tools/Src/queue.o \
./tools/Src/timer_base.o 

C_DEPS += \
./tools/Src/convert.d \
./tools/Src/queue.d \
./tools/Src/timer_base.d 


# Each subdirectory must supply rules for building sources it contributes
tools/Src/%.o tools/Src/%.su tools/Src/%.cyclo: ../tools/Src/%.c tools/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DSTM32 -DSTM32F1 -DSTM32F103C6Tx -DSTM32F103x6 -c -I../Inc -I"C:/Users/nguye/STM32CubeIDE/workspace_1.17.0/SMARTOFFICE/Drivers/Inc" -I"C:/Users/nguye/STM32CubeIDE/workspace_1.17.0/SMARTOFFICE/Drivers/CMSIS/Device/ST/STM32F1xx/Include" -I"C:/Users/nguye/STM32CubeIDE/workspace_1.17.0/SMARTOFFICE/Drivers/CMSIS/Include" -I"C:/Users/nguye/STM32CubeIDE/workspace_1.17.0/SMARTOFFICE/tools/Inc" -I"C:/Users/nguye/STM32CubeIDE/workspace_1.17.0/SMARTOFFICE/Core/Inc" -I"C:/Users/nguye/STM32CubeIDE/workspace_1.17.0/SMARTOFFICE/Sevice/Inc/Com" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-tools-2f-Src

clean-tools-2f-Src:
	-$(RM) ./tools/Src/convert.cyclo ./tools/Src/convert.d ./tools/Src/convert.o ./tools/Src/convert.su ./tools/Src/queue.cyclo ./tools/Src/queue.d ./tools/Src/queue.o ./tools/Src/queue.su ./tools/Src/timer_base.cyclo ./tools/Src/timer_base.d ./tools/Src/timer_base.o ./tools/Src/timer_base.su

.PHONY: clean-tools-2f-Src

