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
        if(sys.lux <300.0f) 
        {
            LED_RGB_SetState(LED_WHITE_100); // Bật đèn LED RGB sáng trắng 100%
            sys.led_r = 255.0f; 
            sys.led_g = 255.0f; 
            sys.led_b = 255.0f;
        }
        else if(sys.lux >= 300.0f && sys.lux < 600.0f) 
        {
            LED_RGB_SetState(LED_WHITE_50); // Bật đèn LED RGB sáng trắng 50%
            sys.led_r = 127.0f; 
            sys.led_g = 127.0f; 
            sys.led_b = 127.0f;
        }
        else if(sys.lux >= 600.0f) 
        {
            LED_RGB_SetState(LED_OFF); // Tắt đèn LED RGB
            sys.led_r = 0.0f; 
            sys.led_g = 0.0f; 
            sys.led_b = 0.0f; 
        }
        else
        {
            // Tắt đèn LED RGB
            LED_RGB_Off();
        }

        if(sys.temperature > 30.0f) 
        {
            Mototr_SetLevel(3); // Bật motor với tốc độ cao
            sys.motor_level = 3.0f; 
            
            sys.motor_dir = 0.0f; 
        }
        else if(sys.temperature <= 30.0f && sys.temperature > 25.0f) 
        {
            Mototr_SetLevel(2);
            sys.motor_level = 2.0f; 
        }
        else if(sys.temperature <= 25.0f && sys.temperature > 20.0f) 
        {
            Mototr_SetLevel(1); // Bật motor với tốc độ thấp
            sys.motor_level = 1.0f; 
        }
        else
        {
            Mototr_SetLevel(0); // Tắt motor
            sys.motor_level = 0.0f; 
        }

        
        while (!empty(&g_uartQueue))
        {
            message_t *message = front(&g_uartQueue);
            if (message == NULL)
            {
                return; // Không có gói tin nào trong hàng đợi
            }

            // Kiểm tra gói tin có hợp lệ không
            if (message->header[0] == COMMAND && message->header[2] == 4 && message->header[1] == AUTO)
            {
                sys.mode = (MODE)Convert_Bytes_To_Int(message->payload[0], message->payload[1], message->payload[2], message->payload[3]);
            }
            // Xóa gói tin đã xử lý khỏi hàng đợi
            pop(&g_uartQueue);
        }
    }
}
