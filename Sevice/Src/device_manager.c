#include "device_manager.h"
#include "uart.h"
#include "globals.h"
#include "message.h"
#include "cds.h"
#include "mq2.h"
#include "dht11.h"
#include "led_rgb.h"
#include "motor.h"
#include "siren.h"

void device_init(void)
{
    DHT11_Init();
    CDS_Init();
    MQ2_Init(10.0f);
    LED_RGB_Init();
    Motor_Init();
    Siren_Init();

    sys.temperature = 25.0f;
    sys.humidity = 50.0f;
    sys.gas_level = 200.0f;
    sys.lux = 500.0f;
    sys.led_r = 255.0f;
    sys.led_g = 255.0f;
    sys.led_b = 255.0f;
    sys.led_state = 0.0f;   // 0: off, 1: on, 2: blink
    sys.motor_level = 0.0f; // 0: off, 1: low, 2: medium, 3: high
    sys.motor_dir = 0.0f;   // 0: forward, 1: backward
    sys.siren_on = 0.0f;    // 0: off, 1: on
    sys.mode = 0.0f;        // 0: auto, 1: manual
}

void READ_Sensor(void)
{
    // DHT11
    uint8_t h, h_d, t, t_d;
    if (DHT11_Read(&h, &h_d, &t, &t_d))
    {
        sys.humidity = h + h_d / 10.0f;    // Độ ẩm (%)
        sys.temperature = t + t_d / 10.0f; // Nhiệt độ (độ C)
    }

    // CDS
    sys.lux = CDS_ReadLux(); // Độ sáng (lux)

    // MQ2
    sys.gas_level = MQ2_ReadAirQuality(); // Nồng độ khí (ppm)
}

void Notify_SendMessage(void)
{
    uint8_t data[20];

    uint8_t length = Create_Message_Notify(DHT11_HUMI, sys.humidity, data);
    USART1_Send_Data(data, length);

    length = Create_Message_Notify(DHT11_TEMP, sys.temperature, data);
    USART1_Send_Data(data, length);

    length = Create_Message_Notify(CDS, sys.lux, data);
    USART1_Send_Data(data, length);

    length = Create_Message_Notify(MQ2, sys.gas_level, data);
    USART1_Send_Data(data, length);

    length = Create_Message_Notify(LED, sys.led_state, data);
    USART1_Send_Data(data, length);

    length = Create_Message_Notify(MOTOR, sys.motor_level, data);
    USART1_Send_Data(data, length);

    length = Create_Message_Notify(SIREN, sys.siren_on, data);
    USART1_Send_Data(data, length);

}
