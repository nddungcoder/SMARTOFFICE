/*
 * mq2.c
 *
 *  Created on: May 22, 2025
 *      Author: nguye
 */

#include "mq2.h"
#include "stm32_adc.h"
#include "stm32_gpio.h"
#include <math.h>

#define MQ2_PORT GPIOA
#define MQ2_PIN (1U << 1) // PA1

#define RL_VALUE 10.0f  // RL = 10kΩ
#define ADC_MAX 4095.0f // 12-bit ADC

// Hệ số từ datasheet MQ2 cho khói (Smoke)
#define SMOKE_A 100.0f
#define SMOKE_B -1.6f

static ADC_HandleTypeDef hadc_mq2;
static float Ro = 10.0f; // Giá trị mặc định Ro

void MQ2_Init(float ro_clean_air)
{
    Ro = ro_clean_air;

    // Bật clock GPIOA nếu chưa bật
    RCC->APB2ENR |= RCC_APB2ENR_IOPAEN;

    // Cấu hình chân analog (ví dụ PA1)
    GPIO_InitTypeDef GPIO_InitStruct = {
        .Pin = MQ2_PIN,
        .Mode = GPIO_MODE_ANALOG};
    GPIO_Init(MQ2_PORT, &GPIO_InitStruct);

    // Cấu hình ADC
    hadc_mq2.Instance = ADC1;
    hadc_mq2.Init.ContinuousConvMode = DISABLE;
    hadc_mq2.Init.DataAlign = ADC_DATAALIGN_RIGHT;
    hadc_mq2.Init.NbrOfConversion = 1;
    hadc_mq2.Init.ScanConvMode = ADC_SCAN_DISABLE;

    ADC_Init(&hadc_mq2);

    ADC_ChannelConfTypeDef sConfig = {
        .Channel = 1, // ADC1_IN1 nếu dùng PA1
        .SamplingTime = ADC_SAMPLETIME_71CYCLES_5};
    ADC_ConfigChannel(&hadc_mq2, &sConfig);
}

static uint16_t MQ2_ReadRaw(void)
{
    ADC_Start(&hadc_mq2);
    ADC_PollForConversion(&hadc_mq2, 1000);
    return (uint16_t)ADC_GetValue(&hadc_mq2);
}

static float MQ2_ReadRs(void)
{
    uint16_t adc_val = MQ2_ReadRaw();
    float voltage_ratio = (ADC_MAX - adc_val) / (float)adc_val;
    return RL_VALUE * voltage_ratio;
}

/**
 * @brief Đọc nồng độ khí tổng quát (Smoke) đại diện cho chất lượng không khí
 * @return ppm
 */
float MQ2_ReadAirQuality(void)
{
    float rs = MQ2_ReadRs();
    float ratio = rs / Ro;
    return SMOKE_A * powf(ratio, SMOKE_B);
}
