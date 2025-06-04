#include "com.h"
#include "fsm_trans.h"

frame_message_t message;
uint8_t uart_buffer[FRAME_MAX_SIZE]; // Bộ đệm để lưu trữ dữ liệu nhận từ UART

/**
 * @brief Khởi tạo giao tiếp UART với tốc độ baud mặc định.
 *
 * @param baud_rate Tốc độ baud, mặc định là 9600.
 */
void COM_Init(uint32_t baud_rate)
{
    Serial1.begin(baud_rate, SERIAL_8N1, 16, 17); // UART1 RX/TX
}

/**
 * @brief Xử lý gói tin UART và cập nhật giá trị thiết bị.
 * @param device Tham chiếu đến đối tượng quản lý thiết bị
 */

void COM_Send_Data(const uint8_t *data, uint8_t length)
{
    for (uint8_t i = 0; i < length; i++)
    {
        Serial1.write(data[i]);
    }
}

void Receive_Handler(device_manager &device, FrameQueue &queue)
{

    while (Serial1.available())
    {
        uint8_t rx = Serial1.read();
        Fsm_Get_Message(rx, uart_buffer);

        if (Check_Fsm_Flag_New_Message())
        {
            if (!Message_Decode(uart_buffer, &message))
            {
                Clear_All_State_Fsm();
                return;
            }

            if (message.header[0] == NOTIFY)
            {
                COM_HandleNotifyMessage(device);
            }
            else if (message.header[0] == RESPONSE)
            {
                COM_HandleResponseMessage(queue);
                return; // Kết thúc hàm sớm để xử lý phản hồi
            }
            Clear_All_State_Fsm();
        }
    }
}

void Transsmit_Handler(FrameQueue &queue)
{
    if (empty(&queue) || Get_Slave_State() == RESPONSE_BUSY)
    {
        return; // Không có dữ liệu để gửi
    }

    frame_message_t *sendmessage = front(&queue);

    switch (Frame_To_Trans())
    {
    case TRANS_STATE_START:
        COM_Send_Data(&sendmessage->start, 1); // Gửi byte START
        break;
    case TRANS_STATE_HEADER:
        COM_Send_Data(sendmessage->header, HEADER_SIZE); // Gửi header (group, id, length)
        break;
    case TRANS_STATE_PAYLOAD:
        COM_Send_Data(sendmessage->payload, sendmessage->header[2]); // Gửi payload
        break;
    case TRANS_STATE_CHECKSUM:
        uint8_t* checksum = Convert_Uint16_To_Bytes(sendmessage->checksum);
        
        COM_Send_Data(checksum, CHECKSUM_SIZE); // Gửi checksum
        break;
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
        frame_message_t *sendmessage = front(&queue);
        Fsm_Trans_Message((RESPONSE_t)message.payload[0], sendmessage);
    }

    if (Check_Flag_Trans_New_Message())
    {
        pop(&queue);
    }
}
