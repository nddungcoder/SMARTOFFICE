#include "auto_mode.h"

#include "globals.h"
#include "convert.h"
#include "queue.h"

#include "led_rgb.h"
#include "motor.h"
#include "siren.h"

#include "uart.h"
#include "message.h"

void Auto_Process(void)
{
    if (sys.mode == AUTO_MODE)
    {
        if (sys.temperature > 35.0f || sys.humidity < 35.0f || sys.gas_level > 500.0f)
        {
            Siren_On();

            LED_RGB_SetState(LED_RED);

            Motor_SetLevel(3);
        }
        else
        {
        	Siren_Off();
            if (sys.lux < 300.0f)
            {
                LED_RGB_SetState(LED_WHITE_100);
            }
            else if (sys.lux >= 300.0f && sys.lux < 600.0f)
            {
                LED_RGB_SetState(LED_WHITE_50);
            }
            else if (sys.lux >= 1200.0f)
            {
                LED_RGB_SetState(LED_OFF);
            }
            else
            {

                LED_RGB_Off();
            }

            if (sys.temperature > 30.0f)
            {
                Motor_SetLevel(3);
            }
            else if (sys.temperature <= 30.0f && sys.temperature > 25.0f)
            {
                Motor_SetLevel(2);
            }
            else if (sys.temperature <= 25.0f && sys.temperature > 20.0f)
            {
                Motor_SetLevel(1);
            }
            else
            {
                Motor_SetLevel(0);
            }
        }

        while (!empty(&g_uartQueue))
        {

            message_t *message = front(&g_uartQueue);

            if (message == NULL)
            {
                return;
            }

            if (message->header[0] == COMMAND && message->header[2] == 4 && message->header[1] == AUTO)
            {

                float mode = Convert_Bytes_To_Float(message->payload[0], message->payload[1], message->payload[2], message->payload[3]);
                if (mode == 1.0f)
                {
                    sys.mode = MANUAL_MODE;
                    uint8_t data[20];
                    uint8_t length = Create_Message_Notify(AUTO, sys.mode, data);
                    USART1_Send_Data(data, length);
                }
            }

            pop(&g_uartQueue);
        }
    }
}
