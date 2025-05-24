/* stm32_tim.c - Minimal Timer HAL Implementation for STM32F103C6T6 */

#include "stm32_tim.h"

HAL_StatusTypeDef TIM_Base_Init(TIM_HandleTypeDef *htim)
{
    if (htim == NULL || htim->Instance == NULL) return HAL_ERROR;

    // Enable timer clock (example: only TIM2 shown here)
    if (htim->Instance == TIM2)
        RCC->APB1ENR |= RCC_APB1ENR_TIM2EN;

    // Basic configuration
    htim->Instance->PSC = htim->Init.Prescaler;
    htim->Instance->ARR = htim->Init.Period;
    htim->Instance->CR1 = htim->Init.CounterMode | htim->Init.ClockDivision;

    return HAL_OK;
}

HAL_StatusTypeDef TIM_PWM_Init(TIM_HandleTypeDef *htim)
{
    return TIM_Base_Init(htim); // For simplicity, PWM init is same as base init
}

HAL_StatusTypeDef TIM_PWM_ConfigChannel(TIM_HandleTypeDef *htim, TIM_OC_InitTypeDef *sConfig, uint32_t Channel)
{
    if (htim == NULL || sConfig == NULL) return HAL_ERROR;

    // Set mode and polarity
    switch (Channel) {
        case TIM_CHANNEL_1:
            htim->Instance->CCMR1 &= ~TIM_CCMR1_OC1M;
            htim->Instance->CCMR1 |= sConfig->OCMode;
            htim->Instance->CCR1 = sConfig->Pulse;
            if (sConfig->OCFastMode == TIM_OCFAST_DISABLE) htim->Instance->CCMR1 &= ~TIM_CCMR1_OC1FE;
            if (sConfig->OCPolarity == TIM_OCPOLARITY_LOW) htim->Instance->CCER |= TIM_CCER_CC1P;
            else htim->Instance->CCER &= ~TIM_CCER_CC1P;
            break;
        case TIM_CHANNEL_2:
            htim->Instance->CCMR1 &= ~TIM_CCMR1_OC2M;
            htim->Instance->CCMR1 |= (sConfig->OCMode << 8);
            htim->Instance->CCR2 = sConfig->Pulse;
            if (sConfig->OCPolarity == TIM_OCPOLARITY_LOW) htim->Instance->CCER |= TIM_CCER_CC2P;
            else htim->Instance->CCER &= ~TIM_CCER_CC2P;
            break;
        case TIM_CHANNEL_3:
            htim->Instance->CCMR2 &= ~TIM_CCMR2_OC3M;
            htim->Instance->CCMR2 |= sConfig->OCMode;
            htim->Instance->CCR3 = sConfig->Pulse;
            if (sConfig->OCPolarity == TIM_OCPOLARITY_LOW) htim->Instance->CCER |= TIM_CCER_CC3P;
            else htim->Instance->CCER &= ~TIM_CCER_CC3P;
            break;
        case TIM_CHANNEL_4:
            htim->Instance->CCMR2 &= ~TIM_CCMR2_OC4M;
            htim->Instance->CCMR2 |= (sConfig->OCMode << 8);
            htim->Instance->CCR4 = sConfig->Pulse;
            if (sConfig->OCPolarity == TIM_OCPOLARITY_LOW) htim->Instance->CCER |= TIM_CCER_CC4P;
            else htim->Instance->CCER &= ~TIM_CCER_CC4P;
            break;
        default:
            return HAL_ERROR;
    }

    return HAL_OK;
}

HAL_StatusTypeDef TIM_PWM_Start(TIM_HandleTypeDef *htim, uint32_t Channel)
{
    switch (Channel) {
        case TIM_CHANNEL_1: htim->Instance->CCER |= TIM_CCER_CC1E; break;
        case TIM_CHANNEL_2: htim->Instance->CCER |= TIM_CCER_CC2E; break;
        case TIM_CHANNEL_3: htim->Instance->CCER |= TIM_CCER_CC3E; break;
        case TIM_CHANNEL_4: htim->Instance->CCER |= TIM_CCER_CC4E; break;
        default: return HAL_ERROR;
    }
    TIM_ENABLE(htim);
    return HAL_OK;
}

HAL_StatusTypeDef TIM_PWM_Stop(TIM_HandleTypeDef *htim, uint32_t Channel)
{
    switch (Channel) {
        case TIM_CHANNEL_1: htim->Instance->CCER &= ~TIM_CCER_CC1E; break;
        case TIM_CHANNEL_2: htim->Instance->CCER &= ~TIM_CCER_CC2E; break;
        case TIM_CHANNEL_3: htim->Instance->CCER &= ~TIM_CCER_CC3E; break;
        case TIM_CHANNEL_4: htim->Instance->CCER &= ~TIM_CCER_CC4E; break;
        default: return HAL_ERROR;
    }
    TIM_DISABLE(htim);
    return HAL_OK;
}
