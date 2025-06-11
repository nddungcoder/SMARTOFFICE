/*
 * siren.c
 *
 *  Created on: May 22, 2025
 *      Author: nguye
 */

#include "siren.h"
#include "stm32_gpio.h"
#include "timer_base.h"

#define SIREN_GPIO_PORT GPIOA
#define SIREN_GPIO_PIN (1U << 3) // PA3

void Siren_Init(void)
{
    GPIO_InitTypeDef gpio = {
        .Pin = SIREN_GPIO_PIN,
        .Mode = GPIO_MODE_OUTPUT_PP,
        .Speed = GPIO_SPEED_HIGH};
    GPIO_Init(SIREN_GPIO_PORT, &gpio);
    GPIO_WritePin(SIREN_GPIO_PORT, SIREN_GPIO_PIN, GPIO_PIN_SET);
}

void Siren_On(void)
{
    GPIO_WritePin(SIREN_GPIO_PORT, SIREN_GPIO_PIN, GPIO_PIN_RESET);
}

void Siren_Off(void)
{
    GPIO_WritePin(SIREN_GPIO_PORT, SIREN_GPIO_PIN, GPIO_PIN_SET);
}

void Siren_Toggle(void)
{
    GPIO_TogglePin(SIREN_GPIO_PORT, SIREN_GPIO_PIN);
}

void Siren_Beep(uint32_t duration_ms)
{
    Siren_On();
    Delay_ms(duration_ms);
    Siren_Off();
}

uint8_t Siren_GetState(void)
{
    GPIO_PinState state = GPIO_ReadPin(SIREN_GPIO_PORT, SIREN_GPIO_PIN);

    // Còi kêu khi pin ở mức RESET (0)
    return (state == GPIO_PIN_RESET) ? 1 : 0;
}
