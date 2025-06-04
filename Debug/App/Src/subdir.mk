################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../App/Src/app_main.c \
../App/Src/auto_mode.c \
../App/Src/manual_mode.c 

OBJS += \
./App/Src/app_main.o \
./App/Src/auto_mode.o \
./App/Src/manual_mode.o 

C_DEPS += \
./App/Src/app_main.d \
./App/Src/auto_mode.d \
./App/Src/manual_mode.d 


# Each subdirectory must supply rules for building sources it contributes
App/Src/%.o App/Src/%.su App/Src/%.cyclo: ../App/Src/%.c App/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DSTM32 -DSTM32F1 -DSTM32F103C6Tx -DSTM32F103x6 -c -I"C:/Users/nguye/STM32CubeIDE/workspace_1.17.0/SMARTOFFICE/Drivers/Inc" -I"C:/Users/nguye/STM32CubeIDE/workspace_1.17.0/SMARTOFFICE/Drivers/CMSIS/Device/ST/STM32F1xx/Include" -I"C:/Users/nguye/STM32CubeIDE/workspace_1.17.0/SMARTOFFICE/Drivers/CMSIS/Include" -I"C:/Users/nguye/STM32CubeIDE/workspace_1.17.0/SMARTOFFICE/tools/Inc" -I"C:/Users/nguye/STM32CubeIDE/workspace_1.17.0/SMARTOFFICE/Sevice/Inc/Com" -I"C:/Users/nguye/STM32CubeIDE/workspace_1.17.0/SMARTOFFICE/Sevice/Inc/Input" -I"C:/Users/nguye/STM32CubeIDE/workspace_1.17.0/SMARTOFFICE/Sevice/Inc/Output" -I"C:/Users/nguye/STM32CubeIDE/workspace_1.17.0/SMARTOFFICE/Sevice/Inc" -I"C:/Users/nguye/STM32CubeIDE/workspace_1.17.0/SMARTOFFICE/App/Inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-App-2f-Src

clean-App-2f-Src:
	-$(RM) ./App/Src/app_main.cyclo ./App/Src/app_main.d ./App/Src/app_main.o ./App/Src/app_main.su ./App/Src/auto_mode.cyclo ./App/Src/auto_mode.d ./App/Src/auto_mode.o ./App/Src/auto_mode.su ./App/Src/manual_mode.cyclo ./App/Src/manual_mode.d ./App/Src/manual_mode.o ./App/Src/manual_mode.su

.PHONY: clean-App-2f-Src

