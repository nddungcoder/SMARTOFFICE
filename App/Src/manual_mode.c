#include "manual_mode.h"
#include "globals.h"

#include "convert.h"
#include "queue.h"
#include "led_rgb.h"
#include "motor.h"
#include "siren.h"

void Manual_Process(void)
{
    while (!empty(&g_uartQueue) && (sys.mode == MANUAL_MODE))
    {
        message_t *message = front(&g_uartQueue);
        if (message == NULL)
        {
            return;
        }
        // Xử lý gói tin trong chế độ Manual
        if (message->header[0] == COMMAND && message->header[2] == 4)
        {
            switch (message->header[1])
            {
            case LED:
                float led_state = Convert_Bytes_To_Float(message->payload[0], message->payload[1], message->payload[2], message->payload[3]);
                LED_RGB_SetState(led_state);
                break;
            case MOTOR:
                float motor_level = Convert_Bytes_To_Float(message->payload[0], message->payload[1], message->payload[2], message->payload[3]);
                Motor_SetLevel(motor_level);

                break;
            case SIREN:
                float siren_on = Convert_Bytes_To_Float(message->payload[0], message->payload[1], message->payload[2], message->payload[3]);
                if (siren_on > 0)
                {
                    Siren_On();
                }
                else
                {
                    Siren_Off();
                }
                break;
            case AUTO:
                float mode = Convert_Bytes_To_Float(message->payload[0], message->payload[1], message->payload[2], message->payload[3]);
                if (mode == 0.0f)
                {
                    sys.mode = AUTO_MODE;
                    uint8_t data[20];
                    uint8_t length = Create_Message_Notify(AUTO, sys.mode, data);
                    USART1_Send_Data(data, length);
                }
                break;
            }
        }
        pop(&g_uartQueue);
    }
}
