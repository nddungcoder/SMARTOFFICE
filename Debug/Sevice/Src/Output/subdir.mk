################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Sevice/Src/Output/led_rgb.c \
../Sevice/Src/Output/motor.c \
../Sevice/Src/Output/siren.c 

OBJS += \
./Sevice/Src/Output/led_rgb.o \
./Sevice/Src/Output/motor.o \
./Sevice/Src/Output/siren.o 

C_DEPS += \
./Sevice/Src/Output/led_rgb.d \
./Sevice/Src/Output/motor.d \
./Sevice/Src/Output/siren.d 


# Each subdirectory must supply rules for building sources it contributes
Sevice/Src/Output/%.o Sevice/Src/Output/%.su Sevice/Src/Output/%.cyclo: ../Sevice/Src/Output/%.c Sevice/Src/Output/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DSTM32 -DSTM32F1 -DSTM32F103C6Tx -DSTM32F103x6 -c -I"C:/Users/nguye/STM32CubeIDE/workspace_1.17.0/SMARTOFFICE/Drivers/Inc" -I"C:/Users/nguye/STM32CubeIDE/workspace_1.17.0/SMARTOFFICE/Drivers/CMSIS/Device/ST/STM32F1xx/Include" -I"C:/Users/nguye/STM32CubeIDE/workspace_1.17.0/SMARTOFFICE/Drivers/CMSIS/Include" -I"C:/Users/nguye/STM32CubeIDE/workspace_1.17.0/SMARTOFFICE/tools/Inc" -I"C:/Users/nguye/STM32CubeIDE/workspace_1.17.0/SMARTOFFICE/Sevice/Inc/Com" -I"C:/Users/nguye/STM32CubeIDE/workspace_1.17.0/SMARTOFFICE/Sevice/Inc/Input" -I"C:/Users/nguye/STM32CubeIDE/workspace_1.17.0/SMARTOFFICE/Sevice/Inc/Output" -I"C:/Users/nguye/STM32CubeIDE/workspace_1.17.0/SMARTOFFICE/Sevice/Inc" -I"C:/Users/nguye/STM32CubeIDE/workspace_1.17.0/SMARTOFFICE/App/Inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Sevice-2f-Src-2f-Output

clean-Sevice-2f-Src-2f-Output:
	-$(RM) ./Sevice/Src/Output/led_rgb.cyclo ./Sevice/Src/Output/led_rgb.d ./Sevice/Src/Output/led_rgb.o ./Sevice/Src/Output/led_rgb.su ./Sevice/Src/Output/motor.cyclo ./Sevice/Src/Output/motor.d ./Sevice/Src/Output/motor.o ./Sevice/Src/Output/motor.su ./Sevice/Src/Output/siren.cyclo ./Sevice/Src/Output/siren.d ./Sevice/Src/Output/siren.o ./Sevice/Src/Output/siren.su

.PHONY: clean-Sevice-2f-Src-2f-Output

