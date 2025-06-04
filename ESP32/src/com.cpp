#include "com.h"

#include "device_manager.h"
#include "driver/uart.h"
#include "freertos/queue.h"
#include "message.h"
#include "device_manager.h"

#define UART_NUM UART_NUM_1
#define UART_RX 16
#define UART_TX 17
#define BUF_SIZE 1024

static QueueHandle_t uart_queue;

extern device_manager device;

extern FrameQueue txQueue;

static message_t message;
uint8_t uart_buffer[FRAME_SIZE]; // Bộ đệm để lưu trữ dữ liệu nhận từ UART

/**
 * @brief Khởi tạo giao tiếp UART với tốc độ baud mặc định.
 *
 * @param baud_rate Tốc độ baud, mặc định là 9600.
 */
void COM_Init(uint32_t baud_rate)
{
    // Tạo hàng đợi UART event (nếu bạn dùng event, nhưng đang NULL ở dưới → chưa cần thiết nếu chỉ dùng polling/interrupt)
    uart_queue = xQueueCreate(20, sizeof(uart_event_t));
    if (uart_queue == NULL)
    {
        Serial.println("Failed to create UART queue");
        return;
    }

    // Cấu hình UART
    uart_config_t uart_config = {
        .baud_rate = (int)baud_rate,
        .data_bits = UART_DATA_8_BITS,
        .parity = UART_PARITY_DISABLE,
        .stop_bits = UART_STOP_BITS_1,
        .flow_ctrl = UART_HW_FLOWCTRL_DISABLE,
        .source_clk = UART_SCLK_APB,
    };

    uart_param_config(UART_NUM, &uart_config);
    uart_set_pin(UART_NUM, UART_TX, UART_RX, UART_PIN_NO_CHANGE, UART_PIN_NO_CHANGE);

    uart_driver_install(UART_NUM, BUF_SIZE * 2, 0, 20, &uart_queue, 0);

    xTaskCreate(uart_event_task, "uart_event_task", 4096, NULL, 12, NULL); // Priority 12 cho task xử lý sự kiện UART

    xTaskCreate(uart_tx_task, "uart_tx_task", 2048, NULL, 10, NULL); // Priority 10 cho task gửi dữ liệu qua UART
}

void uart_event_task(void *pvParameters)
{
    uart_event_t event;
    uint8_t data[BUF_SIZE];

    while (1)
    {
        if (xQueueReceive(uart_queue, &event, portMAX_DELAY))
        {
            if (event.type == UART_DATA)
            {
                int len = uart_read_bytes(UART_NUM, data, event.size, portMAX_DELAY);

                for (int i = 0; i < len; i++)
                {
                    Fsm_Get_Message(data[i], uart_buffer);

                    if (Check_Fsm_Flag_New_Message())
                    {
                        if (Message_Decode(uart_buffer, &message))
                        {
                            if (message.header[0] == NOTIFY)
                            {
                                COM_HandleNotifyMessage(device);
                            }
                            else if (message.header[0] == RESPONSE)
                            {
                                COM_HandleResponseMessage(txQueue);
                            }
                        }

                        Clear_All_State_Fsm();
                    }
                }
            }
        }
    }
}

void uart_tx_task(void *param)
{
    while (1)
    {
        if (!empty(&txQueue))
        {
            Message_Convert_t mes = front(&txQueue);
            if (mes.data != NULL)
            {
                Serial.print("Sending frame: ");
                // Gửi frame qua UART
                uart_write_bytes(UART_NUM, (const char *)mes.data, FRAME_SIZE);
                pop(&txQueue);
            }
        }
        vTaskDelay(10 / portTICK_PERIOD_MS); // Tạm nghỉ, tránh chiếm CPU
    }
}

void COM_HandleNotifyMessage(device_manager &device)
{
    // Serial.print("Notify ");

    if (message.header[2] == 4)
    {
        switch (message.header[1])
        {
        case CDS:
            device.setLdrLuxBytes(message.payload[0], message.payload[1], message.payload[2], message.payload[3]);

            Serial.print(String("CDS "));
            Serial.print(" ");
            Serial.println(device.getLdrLux());
            break;
        case MQ2:
            device.setGasPPMBytes(message.payload[0], message.payload[1], message.payload[2], message.payload[3]);

            Serial.print(String("AIR_QUALITY "));
            Serial.print(" ");
            Serial.println(device.getGasPPM());
            break;
        case DHT11_TEMP:
            device.setDhtTemperatureBytes(message.payload[0], message.payload[1], message.payload[2], message.payload[3]);

            Serial.print(String("DHT11_TEMP "));
            Serial.print(" ");
            Serial.println(device.getDhtTemperature());
            break;
        case DHT11_HUMI:
            device.setDhtHumidityBytes(message.payload[0], message.payload[1], message.payload[2], message.payload[3]);

            Serial.print(String("DHT11_HUMI "));
            Serial.print(" ");
            Serial.println(device.getDhtHumidity());
            break;
        case LED:
            device.setLEDStatusBytes(message.payload[0], message.payload[1], message.payload[2], message.payload[3]);

            Serial.print(String("LED "));
            Serial.print(" ");
            Serial.println(device.getLEDStatus());
            break;
        case MOTOR:
            device.setMotorSpeedBytes(message.payload[0], message.payload[1], message.payload[2], message.payload[3]);

            Serial.print(String("MOTOR "));
            Serial.print(" ");
            Serial.println(device.getMotorSpeed());
            break;
        case SIREN:
            device.setSirenStatusBytes(message.payload[0], message.payload[1], message.payload[2], message.payload[3]);

            Serial.print(String("SIREN "));
            Serial.print(" ");
            Serial.println(device.getSirenStatus());
            break;
        }
    }
}

void COM_HandleResponseMessage(FrameQueue &queue)
{
    if (!empty(&queue))
    {
        if (message.payload[0] == RESPONSE_ACK)
        {
            pop(&queue);
        }
    }
}
