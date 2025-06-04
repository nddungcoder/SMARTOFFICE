/*
 * interrupts.c
 *
 *  Created on: May 29, 2025
 *      Author: nguye
 */

#include "interrupts.h"

#include "stm32_gpio.h"
#include "stm32_adc.h"
#include "stm32_tim.h"
#include "stm32_uart.h"
#include "uart.h"

#include "message.h"
#include "globals.h"

#include "fsm_message.h"

static message_t message;

uint8_t buffer[FRAME_SIZE];

void UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
    if (full(&g_uartQueue))
    {
        // TODO
        return;
    }

    if (huart->Instance == USART1)
    {
        uint8_t length = Fsm_Get_Message(uart_rx_buffer, buffer);
        DUNGX_UART_Receive_IT(&huart1, uart_rx_buffer, length);

        if (Check_Fsm_Flag_New_Message())
        {
            if (Message_Decode(buffer, &message))
            {
                push(&g_uartQueue, message, FRAME_SIZE);

                // ACK
                uint8_t data[FRAME_SIZE];
                uint8_t length = Create_Message_RESPONSE(UNKNOWN, RESPONSE_ACK, data);
                USART1_Send_Data(data, length);
            } else{
                // NACK
                uint8_t data[FRAME_SIZE];
                uint8_t length = Create_Message_RESPONSE(UNKNOWN, RESPONSE_NACK, data);
                USART1_Send_Data(data, length);
            }
            Clear_All_State_Fsm();
        }
        if (full(&g_uartQueue))
        {
            // TODO
        }
        // TODO: TIME OUT
    }
}

void TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
    // Todo
}

void GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
    // Todo
}
