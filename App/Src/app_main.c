#include "app_main.h"
#include "stm32f1xx.h"
#include "stm32_rcc.h"
#include "uart.h"
#include "message.h"
#include "queue.h"
#include "auto_mode.h"
#include "manual_mode.h"
#include "system_manager.h"
#include "timer_base.h"

#include "dht11.h"
#include "mq2.h"
UART_HandleTypeDef huart1;
FrameQueue g_uartQueue;
uint8_t uart_rx_buffer[FRAME_SIZE];

SystemState sys;

void App_Init(void)
{
    SystemClock_Config();
    USART1_Init(115200);
    Timer_Init();
    Queue_init(&g_uartQueue);
    device_init();
    DUNGX_UART_Receive_IT(&huart1, uart_rx_buffer, 2);
}

void App_Loop(void)
{
	static uint32_t lastDeviceUpdateTick = 0; // Cho 200ms
	    static uint32_t lastProcessTick = 0;      // Cho 50ms

	    uint32_t currentTick = GetTick(); // tick_ms hiện tại

	    // Task 1: Update device mỗi 200ms
	    if ((currentTick - lastDeviceUpdateTick) >= 200)
	    {
	        DeviceManager_UpdateData();
	        lastDeviceUpdateTick = currentTick;
	    }

	    // Task 2: Xử lý chế độ mỗi 50ms
	    if ((currentTick - lastProcessTick) >= 50)
	    {
	        if (sys.mode == AUTO_MODE)
	        {
	            Auto_Process();
	        }
	        else if (sys.mode == MANUAL_MODE)
	        {
	            Manual_Process();
	        }

	        lastProcessTick = currentTick;
	    }
}
