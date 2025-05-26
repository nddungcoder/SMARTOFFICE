#ifndef __TIMER_BASE_H__
#define __TIMER_BASE_H__

#include "stm32_tim.h"             

void Timer2_Init(void);
void Delay_us(uint16_t us);
void Delay_ms(uint32_t ms);
uint32_t millis(void);
void TIM2_IRQHandler(void);

#endif