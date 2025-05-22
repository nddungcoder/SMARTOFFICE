/*
 * stm32_gpio.h
 *
 *  Created on: May 15, 2025
 *      Author: nguye
 */

#ifndef INC_STM32_GPIO_H_
#define INC_STM32_GPIO_H_

#include "stm32f1.h"

typedef struct
{
	uint8_t GPIO_PinNumber;
	uint8_t GPIO_PinMode;
	uint8_t GPIO_PinSpeed;
	uint8_t GPIO_PinPuPdControll;
	uint8_t GPIO_PinOPType;
	uint8_t GPIO_PinAltFunMode;
}GPIO_PinConfig_t;

typedef struct
{
	GPIO_RegDef_t *pGPIOx;
	GPIO_PinConfig_t GPIO_PinConfig;
}GPIO_Handle_t;

#define GPIO_PIN_NO_0 0
#define GPIO_PIN_NO_1 1
#define GPIO_PIN_NO_2 2
#define GPIO_PIN_NO_3 3
#define GPIO_PIN_NO_4 4
#define GPIO_PIN_NO_5 5
#define GPIO_PIN_NO_6 6
#define GPIO_PIN_NO_7 7
#define GPIO_PIN_NO_8 8
#define GPIO_PIN_NO_9 9
#define GPIO_PIN_NO_10 10
#define GPIO_PIN_NO_11 11
#define GPIO_PIN_NO_12 12
#define GPIO_PIN_NO_13 13
#define GPIO_PIN_NO_14 14
#define GPIO_PIN_NO_15 15

// GPIO Pin modes
#define GPIO_MODE_INPUT        0
#define GPIO_MODE_OUTPUT_PP    1
#define GPIO_MODE_OUTPUT_OD    2
#define GPIO_MODE_AF_PP        3
#define GPIO_MODE_AF_OD        4
#define GPIO_MODE_ANALOG       5
#define GPIO_MODE_INPUT_PD     6
#define GPIO_MODE_INPUT_PU     7
#define GPIO_MODE_IT_FT        8
#define GPIO_MODE_IT_RT        9
#define GPIO_MODE_IT_RFT       10

// GPIO Speed
#define GPIO_SPEED_LOW         0
#define GPIO_SPEED_MEDIUM      1
#define GPIO_SPEED_HIGH        2

void GPIO_PeriClockControl(GPIO_RegDef_t * pGPIOx, uint8_t EnOrDi);
void GPIO_Init(GPIO_Handle_t *pGPIOHandle);

void GPIO_DeInit(GPIO_RegDef_t *pGPIOx);

uint8_t GPIO_ReadFromPin(GPIO_RegDef_t *pGPIOx, uint8_t PinNumber);
uint16_t GPIO_ReadFromPort(GPIO_RegDef_t *pGPIOx);

void GPIO_WriteToPin(GPIO_RegDef_t *pGPIOx, uint8_t PinNumber, uint8_t Value);
void GPIO_WriteToPort(GPIO_RegDef_t *pGPIOx, uint16_t Value);

void GPIO_TogglePin(GPIO_RegDef_t *pGPIOx, uint8_t PinNumber);

void GPIO_IRQInterruptConfig(uint8_t IRQNumber, uint8_t EnOrDi);
void GPIO_IRQPriorityConfig(uint8_t IRQNumber, uint32_t IRQPriority);
void GPIO_IRQHandling(uint8_t PinNumber);




#endif /* INC_STM32_GPIO_H_ */
