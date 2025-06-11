#include "adc_sensor.h"
#include "stm32_adc.h"
#include "stm32_gpio.h"

// ===== Hardware Definitions =====
#define CDS_CHANNEL     0  // ADC1_IN0 -> PA0
#define MQ2_CHANNEL     1  // ADC1_IN1 -> PA1

#define ADC_SAMPLING_TIME ADC_SAMPLETIME_71CYCLES_5

static ADC_HandleTypeDef hadc1;
static uint16_t adc_values[2];

void ADC_Sensor_Init(void)
{
    // 1. Init GPIO PA0, PA1 as analog
    GPIO_InitTypeDef gpio = {
        .Mode = GPIO_MODE_ANALOG,
        .Pin = (1U << 0) | (1U << 1) // PA0 + PA1
    };
    GPIO_Init(GPIOA, &gpio);

    // 2. Init ADC1 for 2 channels with scan mode
    hadc1.Instance = ADC1;
    hadc1.Init.ContinuousConvMode = DISABLE;
    hadc1.Init.DataAlign = ADC_DATAALIGN_RIGHT;
    hadc1.Init.ScanConvMode = ADC_SCAN_ENABLE;
    hadc1.Init.NbrOfConversion = 2;
    ADC_Init(&hadc1);

    // 3. Config each channel with rank
    ADC_ChannelConfTypeDef config;

    config.Channel = CDS_CHANNEL;
    config.Rank = 1;
    config.SamplingTime = ADC_SAMPLING_TIME;
    ADC_ConfigChannel(&hadc1, &config);

    config.Channel = MQ2_CHANNEL;
    config.Rank = 2;
    config.SamplingTime = ADC_SAMPLING_TIME;
    ADC_ConfigChannel(&hadc1, &config);
}

void ADC_Sensor_ReadAll(void)
{
    ADC_ReadAll(&hadc1, adc_values, 2);
}

uint16_t ADC_CDS_GetRaw(void)
{
    return adc_values[0];
}

uint16_t ADC_MQ2_GetRaw(void)
{
    return adc_values[1];
}

float ADC_CDS_GetLux(void)
{
    return (4095.0f - adc_values[0]) * 2000.0f / 4095.0f;
}

float ADC_MQ2_GetLevel(void)
{
    return adc_values[1] * 2000.0f / 4095.0f;
}
