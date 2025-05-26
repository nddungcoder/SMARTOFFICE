/* stm32_gpio.c - Minimal GPIO HAL Implementation for STM32F103C6T6 with EXTI */

#include "stm32_gpio.h"

void GPIO_Init(GPIO_TypeDef *GPIOx, GPIO_InitTypeDef *GPIO_Init)
{
    uint32_t pos = 0;
    while ((GPIO_Init->Pin >> pos) != 0x00u)
    {
        if ((GPIO_Init->Pin & (1u << pos)) != 0)
        {
            uint32_t shift = (pos % 8) * 4;
            __IO uint32_t *reg = (pos < 8) ? &GPIOx->CRL : &GPIOx->CRH;

            *reg &= ~(0xFu << shift);

            if (GPIO_Init->Mode == GPIO_MODE_INPUT)
            {
                if (GPIO_Init->Pull == GPIO_PULLUP)
                {
                    *reg |= (0x08u << shift); // CNF = 10 input PU/PD
                    GPIOx->BSRR = (1u << pos);
                }
                else if (GPIO_Init->Pull == GPIO_PULLDOWN)
                {
                    *reg |= (0x08u << shift); // CNF = 10 input PU/PD
                    GPIOx->BRR = (1u << pos);
                }
                else
                {
                    *reg |= (0x04u << shift); // CNF = 01 floating
                }
            }
            else if (GPIO_Init->Mode == GPIO_MODE_ANALOG)
            {
                *reg |= (0x00u << shift); // CNF = 00 analog
            }
            else // Output or AF
            {
                uint32_t mode = 0x00u;
                if (GPIO_Init->Speed == GPIO_SPEED_LOW) mode = 0x02;
                else if (GPIO_Init->Speed == GPIO_SPEED_MEDIUM) mode = 0x01;
                else mode = 0x03;

                uint32_t cnf = 0;
                if (GPIO_Init->Mode == GPIO_MODE_OUTPUT_PP) cnf = 0x00;
                else if (GPIO_Init->Mode == GPIO_MODE_OUTPUT_OD) cnf = 0x04;
                else if (GPIO_Init->Mode == GPIO_MODE_AF_PP) cnf = 0x08;
                else if (GPIO_Init->Mode == GPIO_MODE_AF_OD) cnf = 0x0C;

                *reg |= ((mode | cnf) << shift);
            }

            // EXTI configuration if needed
            if ((GPIO_Init->Mode & 0x10000000u) != 0)
            {
                uint32_t exti_line = 1u << pos;
                AFIO->EXTICR[pos >> 2] &= ~(0xFu << (4 * (pos & 0x03)));
                AFIO->EXTICR[pos >> 2] |= ((GPIOx == GPIOA ? 0 : (GPIOx == GPIOB ? 1 : 2)) << (4 * (pos & 0x03)));

                if (GPIO_Init->Mode & 0x00100000u) EXTI->RTSR |= exti_line; else EXTI->RTSR &= ~exti_line;
                if (GPIO_Init->Mode & 0x00200000u) EXTI->FTSR |= exti_line; else EXTI->FTSR &= ~exti_line;

                EXTI->IMR |= exti_line;
            }
        }
        pos++;
    }
}

void GPIO_WritePin(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin, GPIO_PinState PinState)
{
    if (PinState != GPIO_PIN_RESET)
        GPIOx->BSRR = GPIO_Pin;
    else
        GPIOx->BRR = GPIO_Pin;
}

GPIO_PinState GPIO_ReadPin(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin)
{
    return (GPIOx->IDR & GPIO_Pin) ? GPIO_PIN_SET : GPIO_PIN_RESET;
}

void GPIO_TogglePin(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin)
{
    GPIOx->ODR ^= GPIO_Pin;
}

void GPIO_EXTI_IRQHandler(uint16_t GPIO_Pin)
{
    if (EXTI->PR & GPIO_Pin)
    {
        EXTI->PR = GPIO_Pin;
        GPIO_EXTI_Callback(GPIO_Pin);
    }
}

__weak void GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
    // Override in user file
}
