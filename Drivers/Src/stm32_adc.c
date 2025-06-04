/* stm32_adc.c - Minimal ADC Driver for STM32F103C6T6 */

#include "stm32_adc.h"

StatusTypeDef ADC_Init(ADC_HandleTypeDef* hadc)
{
    if (hadc == NULL || hadc->Instance != ADC1) {
        return DUNGX_ERROR;
    }

    // Enable ADC1 clock
    RCC->APB2ENR |= RCC_APB2ENR_ADC1EN;

    // Reset CR1 and CR2
    hadc->Instance->CR1 = 0;
    hadc->Instance->CR2 = 0;

    // Set scan mode
    if (hadc->Init.ScanConvMode == ADC_SCAN_ENABLE) {
        hadc->Instance->CR1 |= ADC_SCAN_ENABLE;
    }

    // Set data alignment
    if (hadc->Init.DataAlign == ADC_DATAALIGN_LEFT) {
        hadc->Instance->CR2 |= ADC_DATAALIGN_LEFT;
    }

    // Set continuous conversion
    if (hadc->Init.ContinuousConvMode == ENABLE) {
        hadc->Instance->CR2 |= ADC_CR2_CONT;
    }

    // Set number of conversions
    hadc->Instance->SQR1 &= ~ADC_SQR1_L;
    hadc->Instance->SQR1 |= (hadc->Init.NbrOfConversion - 1) << 20;

    // Enable ADC
    ADC_ENABLE(hadc);

    // Short delay before calibration
    for (volatile int i = 0; i < 1000; ++i);

    // Calibration
    hadc->Instance->CR2 |= ADC_CR2_CAL;
    while (hadc->Instance->CR2 & ADC_CR2_CAL);

    return DUNGX_OK;
}

StatusTypeDef ADC_ConfigChannel(ADC_HandleTypeDef* hadc, ADC_ChannelConfTypeDef* sConfig)
{
    if (hadc == NULL || sConfig == NULL) {
        return DUNGX_ERROR;
    }

    // Configure channel rank in regular sequence
    hadc->Instance->SQR3 &= ~ADC_SQR3_SQ1;
    hadc->Instance->SQR3 |= sConfig->Channel;

    // Configure sample time (only SMP0 used here for simplicity)
    hadc->Instance->SMPR2 &= ~ADC_SMPR2_SMP0;
    hadc->Instance->SMPR2 |= sConfig->SamplingTime;

    return DUNGX_OK;
}

StatusTypeDef ADC_Start(ADC_HandleTypeDef* hadc)
{
    if (hadc == NULL) {
        return DUNGX_ERROR;
    }

    // Start conversion
    hadc->Instance->CR2 |= ADC_CR2_ADON;  // First write to ADON turns ADC on
    hadc->Instance->CR2 |= ADC_CR2_ADON;  // Second write starts conversion

    return DUNGX_OK;
}

StatusTypeDef ADC_PollForConversion(ADC_HandleTypeDef* hadc, uint32_t Timeout)
{
    if (hadc == NULL) {
        return DUNGX_ERROR;
    }

    while (!(hadc->Instance->SR & ADC_SR_EOC)) {
        if (Timeout-- == 0) return DUNGX_TIMEOUT;
    }

    return DUNGX_OK;
}

uint32_t ADC_GetValue(ADC_HandleTypeDef* hadc)
{
    if (hadc == NULL) return 0;
    return hadc->Instance->DR;
}
