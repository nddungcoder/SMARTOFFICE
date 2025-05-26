################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Sevice/Src/Input/cds.c \
../Sevice/Src/Input/dht11.c \
../Sevice/Src/Input/ir.c \
../Sevice/Src/Input/mic.c \
../Sevice/Src/Input/mq2.c 

OBJS += \
./Sevice/Src/Input/cds.o \
./Sevice/Src/Input/dht11.o \
./Sevice/Src/Input/ir.o \
./Sevice/Src/Input/mic.o \
./Sevice/Src/Input/mq2.o 

C_DEPS += \
./Sevice/Src/Input/cds.d \
./Sevice/Src/Input/dht11.d \
./Sevice/Src/Input/ir.d \
./Sevice/Src/Input/mic.d \
./Sevice/Src/Input/mq2.d 


# Each subdirectory must supply rules for building sources it contributes
Sevice/Src/Input/%.o Sevice/Src/Input/%.su Sevice/Src/Input/%.cyclo: ../Sevice/Src/Input/%.c Sevice/Src/Input/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DSTM32 -DSTM32F1 -DSTM32F103C6Tx -DSTM32F103x6 -c -I../Inc -I"C:/Users/nguye/STM32CubeIDE/workspace_1.17.0/SMARTOFFICE/Drivers/Inc" -I"C:/Users/nguye/STM32CubeIDE/workspace_1.17.0/SMARTOFFICE/Drivers/CMSIS/Device/ST/STM32F1xx/Include" -I"C:/Users/nguye/STM32CubeIDE/workspace_1.17.0/SMARTOFFICE/Drivers/CMSIS/Include" -I"C:/Users/nguye/STM32CubeIDE/workspace_1.17.0/SMARTOFFICE/tools/Inc" -I"C:/Users/nguye/STM32CubeIDE/workspace_1.17.0/SMARTOFFICE/Core/Inc" -I"C:/Users/nguye/STM32CubeIDE/workspace_1.17.0/SMARTOFFICE/Sevice/Inc/Com" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Sevice-2f-Src-2f-Input

clean-Sevice-2f-Src-2f-Input:
	-$(RM) ./Sevice/Src/Input/cds.cyclo ./Sevice/Src/Input/cds.d ./Sevice/Src/Input/cds.o ./Sevice/Src/Input/cds.su ./Sevice/Src/Input/dht11.cyclo ./Sevice/Src/Input/dht11.d ./Sevice/Src/Input/dht11.o ./Sevice/Src/Input/dht11.su ./Sevice/Src/Input/ir.cyclo ./Sevice/Src/Input/ir.d ./Sevice/Src/Input/ir.o ./Sevice/Src/Input/ir.su ./Sevice/Src/Input/mic.cyclo ./Sevice/Src/Input/mic.d ./Sevice/Src/Input/mic.o ./Sevice/Src/Input/mic.su ./Sevice/Src/Input/mq2.cyclo ./Sevice/Src/Input/mq2.d ./Sevice/Src/Input/mq2.o ./Sevice/Src/Input/mq2.su

.PHONY: clean-Sevice-2f-Src-2f-Input

