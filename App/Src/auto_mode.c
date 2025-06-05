#include "auto_mode.h"

#include "globals.h"
#include "convert.h"
#include "queue.h"

#include "led_rgb.h"
#include "motor.h"
#include "siren.h"

void Auto_Process(void)
{
    if (sys.mode == AUTO_MODE)
    {
        if (sys.temperature > 35.0f || sys.humidity < 30.0f || sys.gas_level > 300.0f)
        {
            Siren_On();
            sys.siren_on = 1.0f;

            LED_RGB_SetState(LED_RED);
            sys.led_state = LED_RED;
            return;
        }

        if (sys.lux < 300.0f)
        {
            LED_RGB_SetState(LED_WHITE_100);
        }
        else if (sys.lux >= 300.0f && sys.lux < 600.0f)
        {
            LED_RGB_SetState(LED_WHITE_50);
        }
        else if (sys.lux >= 600.0f)
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
            sys.motor_level = 3.0f;

            sys.motor_dir = 0.0f;
        }
        else if (sys.temperature <= 30.0f && sys.temperature > 25.0f)
        {
            Motor_SetLevel(2);
            sys.motor_level = 2.0f;
        }
        else if (sys.temperature <= 25.0f && sys.temperature > 20.0f)
        {
            Motor_SetLevel(1);
            sys.motor_level = 1.0f;
        }
        else
        {
            Motor_SetLevel(0);
            sys.motor_level = 0.0f;
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
                sys.mode = Convert_Bytes_To_Float(message->payload[0], message->payload[1], message->payload[2], message->payload[3]);
            }

            pop(&g_uartQueue);
        }
    }
}
