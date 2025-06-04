#ifndef GLOBALS_H
#define GLOBALS_H

#include "uart.h"
#include "queue.h"
#include "app_main.h"

extern UART_HandleTypeDef huart1;

extern FrameQueue g_uartQueue;
extern uint8_t uart_rx_buffer[FRAME_SIZE];


extern SystemState sys;


#endif
