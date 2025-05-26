/* stm32_uart.h - Minimal UART HAL Interface for STM32F103C6T6 */

#ifndef __STM32_UART_H
#define __STM32_UART_H

#ifdef __cplusplus
extern "C" {
#endif

#include "stm32f1xx_hal_def.h"

/* UART Initialization Structure */
typedef struct {
  uint32_t BaudRate;     // Baud rate e.g. 9600, 115200
  uint32_t WordLength;   // UART_WORDLENGTH_8B
  uint32_t StopBits;     // UART_STOPBITS_1
  uint32_t Parity;       // UART_PARITY_NONE
  uint32_t Mode;         // UART_MODE_TX_RX
  uint32_t HwFlowCtl;    // UART_HWCONTROL_NONE
  uint32_t OverSampling; // UART_OVERSAMPLING_16
} UART_InitTypeDef;

/* UART Handle Structure */
typedef struct __UART_HandleTypeDef {
  USART_TypeDef *Instance;      // USARTx instance (e.g. USART1)
  UART_InitTypeDef Init;        // UART configuration
  __IO uint32_t State;          // UART state
  __IO uint32_t ErrorCode;      // Error code
} UART_HandleTypeDef;

/* UART Word Length */
#define UART_WORDLENGTH_8B        ((uint32_t)0x00000000U)

/* UART Stop Bits */
#define UART_STOPBITS_1           ((uint32_t)0x00000000U)

/* UART Parity */
#define UART_PARITY_NONE          ((uint32_t)0x00000000U)

/* UART Mode */
#define UART_MODE_TX              ((uint32_t)USART_CR1_TE)
#define UART_MODE_RX              ((uint32_t)USART_CR1_RE)
#define UART_MODE_TX_RX           ((uint32_t)(USART_CR1_TE | USART_CR1_RE))

/* UART Hardware Flow Control */
#define UART_HWCONTROL_NONE       ((uint32_t)0x00000000U)

/* UART Oversampling */
#define UART_OVERSAMPLING_16      ((uint32_t)0x00000000U)

/* UART Exported Functions */
HAL_StatusTypeDef UART_Init(UART_HandleTypeDef *huart);
HAL_StatusTypeDef UART_Transmit(UART_HandleTypeDef *huart, uint8_t *pData, uint16_t Size, uint32_t Timeout);
HAL_StatusTypeDef UART_Receive(UART_HandleTypeDef *huart, uint8_t *pData, uint16_t Size, uint32_t Timeout);

#ifdef __cplusplus
}
#endif

#endif /* __STM32_UART_H */
