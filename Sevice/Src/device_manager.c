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
    Siren_Init();
    Motor_Init();

    sys.temperature = 25.0f;
    sys.humidity = 50.0f;
    sys.gas_level = 200.0f;
    sys.lux = 500.0f;
    sys.led_state = 0.0f;   // 0: off, 1: WHITE, 2: SOFT WHITE, 3: GREEN, 4: RED
    sys.motor_level = 2.0f; // 0: off, 1: low, 2: medium, 3: high
    sys.motor_dir = 0.0f;   // 0: forward, 1: backward
    sys.siren_on = 0.0f;    // 0: off, 1: on
    sys.mode = 0.0f;        // 0: auto, 1: manual
}

void DeviceManager_UpdateData(void)
{
    uint8_t data[20];
    uint8_t length;

    // ======= DHT11 =======
    uint8_t h, h_d, t, t_d;
    if (DHT11_Read(&h, &h_d, &t, &t_d))
    {
        float humidity = h + h_d / 10.0f;
        float temperature = t + t_d / 10.0f;

        if (humidity != sys.humidity)
        {
            sys.humidity = humidity;

            length = Create_Message_Notify(DHT11_HUMI, sys.humidity, data);
            USART1_Send_Data(data, length);
        }

        if (temperature != sys.temperature)
        {
            sys.temperature = temperature;

            length = Create_Message_Notify(DHT11_TEMP, sys.temperature, data);
            USART1_Send_Data(data, length);
        }
    }

    // ======= CDS =======
    float lux = CDS_ReadLux();
    if (lux != sys.lux)
    {
        sys.lux = lux;

        length = Create_Message_Notify(CDS, sys.lux, data);
        USART1_Send_Data(data, length);
    }

    // ======= MQ2 =======
    float gas = MQ2_ReadAirQuality();
    if (gas != sys.gas_level)
    {
        sys.gas_level = gas;

        length = Create_Message_Notify(MQ2, sys.gas_level, data);
        USART1_Send_Data(data, length);
    }

    // ======= actuator =======
    if (sys.mode == AUTO_MODE)
    {
        length = Create_Message_Notify(LED, sys.led_state, data);
        USART1_Send_Data(data, length);

        length = Create_Message_Notify(MOTOR, sys.motor_level, data);
        USART1_Send_Data(data, length);

        length = Create_Message_Notify(SIREN, sys.siren_on, data);
        USART1_Send_Data(data, length);
    }
}
