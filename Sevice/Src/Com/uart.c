/*
 * uart.c
 *
 *  Created on: May 22, 2025
 *      Author: nguye
 */

 #include "uart.h"

// Bộ xử lý UART toàn cục cho USART1
UART_HandleTypeDef huart1;

/**
 * @brief Khởi tạo USART1 với tốc độ baud được chỉ định.
 */
void USART1_Init(uint32_t baud_rate)
{
    huart1.Instance = USART1;
    huart1.Init.BaudRate = baud_rate;
    // Word length 8-bit => M = 0 (bit 12 clear)
    huart1.Init.WordLength = 0;


    huart1.Init.StopBits = 0;                              // 1 stop bit (mặc định)
    huart1.Init.Parity = USART_CR1_PCE & ~USART_CR1_PCE;   // No parity
    huart1.Init.Mode = USART_CR1_TE | USART_CR1_RE;        // TX + RX
    huart1.Init.HwFlowCtl = 0;

    UART_Init(&huart1); // Gọi hàm từ stm32_uart.c
}

/**
 * @brief Gửi một ký tự qua USART1.
 */
void USART1_Send_Char(char chr)
{
    UART_Transmit(&huart1, (uint8_t*)&chr, 1, 1000);
}

/**
 * @brief Gửi một chuỗi null-terminated qua USART1.
 */
void USART1_Send_String(char* str)
{
    if (str != NULL)
    {
        UART_Transmit(&huart1, (uint8_t*)str, strlen(str), 1000);
    }
}

/**
 * @brief Gửi một mảng dữ liệu qua USART1.
 */
void USART1_Send_Data(uint8_t* data, uint8_t length)
{
    if (data != NULL && length > 0)
    {
        UART_Transmit(&huart1, data, length, 1000);
    }
}

/**
 * @brief Gửi số nguyên dưới dạng chuỗi qua USART1.
 */
void USART1_Send_Number(int16_t num)
{
    char buffer[8];
    sprintf(buffer, "%d", num);
    USART1_Send_String(buffer);
}

/**
 * @brief Gửi số thực dưới dạng chuỗi qua USART1.
 */
void USART1_Send_Float(float num)
{
    char buffer[16];
    sprintf(buffer, "%.2f", num);  // 2 chữ số sau dấu thập phân
    USART1_Send_String(buffer);
}

/**
 * @brief Gửi 1 byte dạng hex
 */
void USART1_Send_Hex(uint8_t num)
{
    char hexStr[3];
    sprintf(hexStr, "%02X", num);
    USART1_Send_String(hexStr);
}



