/* stm32_uart.c - Minimal UART HAL Implementation for STM32F103C6T6 */

#include "stm32_uart.h"

HAL_StatusTypeDef UART_Init(UART_HandleTypeDef *huart)
{
    if (huart == NULL || huart->Instance == NULL) return HAL_ERROR;

    // Enable USART clock (example: USART1 only)
    if (huart->Instance == USART1) {
        RCC->APB2ENR |= RCC_APB2ENR_USART1EN;
    }

    // Configure baud rate (assuming PCLK2 = 72MHz)
    uint32_t pclk = 72000000;
    huart->Instance->BRR = (pclk + huart->Init.BaudRate / 2) / huart->Init.BaudRate;

    // Configure word length, parity, and mode
    huart->Instance->CR1 = huart->Init.WordLength |
                           huart->Init.Parity |
                           huart->Init.Mode;

    // Enable USART
    huart->Instance->CR1 |= USART_CR1_UE;

    return HAL_OK;
}

HAL_StatusTypeDef UART_Transmit(UART_HandleTypeDef *huart, uint8_t *pData, uint16_t Size, uint32_t Timeout)
{
    if (huart == NULL || pData == NULL || Size == 0) return HAL_ERROR;

    while (Size--) {
        // Wait until TXE (Transmit Data Register Empty)
        while (!(huart->Instance->SR & USART_SR_TXE)) {
            if (Timeout-- == 0) return HAL_TIMEOUT;
        }

        huart->Instance->DR = (*pData++ & 0xFF);
    }

    // Wait for TC (Transmission Complete)
    while (!(huart->Instance->SR & USART_SR_TC)) {
        if (Timeout-- == 0) return HAL_TIMEOUT;
    }

    return HAL_OK;
}

HAL_StatusTypeDef UART_Receive(UART_HandleTypeDef *huart, uint8_t *pData, uint16_t Size, uint32_t Timeout)
{
    if (huart == NULL || pData == NULL || Size == 0) return HAL_ERROR;

    while (Size--) {
        // Wait until RXNE (Read Data Register Not Empty)
        while (!(huart->Instance->SR & USART_SR_RXNE)) {
            if (Timeout-- == 0) return HAL_TIMEOUT;
        }

        *pData++ = (uint8_t)(huart->Instance->DR & 0xFF);
    }

    return HAL_OK;
}
