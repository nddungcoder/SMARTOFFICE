#ifndef __ADC_SENSOR_H__
#define __ADC_SENSOR_H__

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

void ADC_Sensor_Init(void);
void ADC_Sensor_ReadAll(void);

uint16_t ADC_CDS_GetRaw(void);
uint16_t ADC_MQ2_GetRaw(void);

float ADC_CDS_GetLux(void);
float ADC_MQ2_GetLevel(void);

#ifdef __cplusplus
}
#endif

#endif
