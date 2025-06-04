#include "fsm_message.h"
#include <string.h>
#include "message.h"
#include "uart.h"

static fsm_state_t fsm_state = FSM_STATE_START; // Trạng thái hiện tại của FSM
static uint8_t byte_count = 0;                  // Số byte đã nhận
static uint8_t expected_payload_length = 0;     // Độ dài payload lấy từ header
static uint8_t flag_fsm_new_message = 0;        // Cờ đã nhận xong frame hợp lệ

/**
 * @brief Đặt lại FSM về trạng thái ban đầu.
 *
 * Hàm này sẽ xóa bộ đếm, cờ trạng thái, dữ liệu đang lưu tạm, và đưa FSM
 * về trạng thái sẵn sàng nhận frame mới từ đầu.
 */
void Clear_All_State_Fsm(void)
{
    fsm_state = FSM_STATE_START;
    byte_count = 0;
    expected_payload_length = 0;
    flag_fsm_new_message = 0;
}

/**
 * @brief Nhận 1 byte dữ liệu từ UART và xử lý theo FSM để xây dựng frame.
 *
 * @param datain Byte dữ liệu đầu vào từ UART.
 * @param dataout Mảng dùng để lưu frame hợp lệ nếu nhận thành công.
 * @return Số byte đã nhận thành công từ UART.
 *
 * Nếu frame hợp lệ và đủ, dữ liệu sẽ được sao chép vào dataout và
 * FSM sẽ chuyển về trạng thái chờ frame mới.
 */
uint8_t Fsm_Get_Message(uint8_t datain[], uint8_t dataout[])
{
    if (flag_fsm_new_message)
        return 1;
    uint8_t length = 1;

    switch (fsm_state)
    {
    case FSM_STATE_START:

        dataout[0] = datain[0];

        if (byte_count == 0 && datain[0] == START_BYTE)
        {
            // Nếu byte đầu tiên là START_BYTE, chuyển sang trạng thái HEADER
            Clear_All_State_Fsm();
            fsm_state = FSM_STATE_HEADER;
            byte_count++;
            length = HEADER_SIZE;
        }
        else
        {
            Clear_All_State_Fsm();

            // NACK
            uint8_t data[FRAME_SIZE];
            uint8_t length = Create_Message_RESPONSE(UNKNOWN, RESPONSE_NACK, data);
            USART1_Send_Data(data, length);
        }
        break;

    case FSM_STATE_HEADER:
        if (byte_count == 1 && Check_Frame_Header(datain))
        {
            GPIOA->ODR ^= (1 << 5);
            for (int i = 0; i < HEADER_SIZE; i++)
            {
                dataout[byte_count] = datain[i];
                byte_count++;
            }
            expected_payload_length = datain[2];

            fsm_state = FSM_STATE_PAYLOAD;

            length = expected_payload_length;
        }
        else
        {
            // NACK
            uint8_t data[FRAME_SIZE];
            uint8_t length = Create_Message_RESPONSE(dataout[2], RESPONSE_NACK, data);
            USART1_Send_Data(data, length); // Gửi phản hồi NACK
        }
        break;

    case FSM_STATE_PAYLOAD:
        if (byte_count == (1 + HEADER_SIZE))
        {
            for (int i = 0; i < 4; i++)
            {
                dataout[byte_count] = datain[i];
                byte_count++;
            }
            fsm_state = FSM_STATE_CHECKSUM;

            length = CHECKSUM_SIZE;
        }
        else
        {
            length = CHECKSUM_SIZE;
            Clear_All_State_Fsm();
            uint8_t data[FRAME_SIZE];
            uint8_t length = Create_Message_RESPONSE(dataout[2], RESPONSE_NACK, data);
            USART1_Send_Data(data, length); // Gửi phản hồi NACK
        }
        break;

    case FSM_STATE_CHECKSUM:

        for (int i = 0; i < CHECKSUM_SIZE; i++)
        {
            dataout[byte_count] = datain[i];
            byte_count++;
        }

        uint16_t received_checksum = Convert_Bytes_To_Uint16(
            dataout[byte_count - 2], dataout[byte_count - 1]);

        uint16_t calculated_checksum = Message_Calculate_Checksum(
            dataout, byte_count - CHECKSUM_SIZE);

        if (byte_count == (1 + HEADER_SIZE + expected_payload_length + CHECKSUM_SIZE) &&
            (received_checksum == calculated_checksum))
        {
            flag_fsm_new_message = 1;
            fsm_state = FSM_STATE_START;
        }
        else {
            Clear_All_State_Fsm();
            uint8_t data[FRAME_SIZE];
                        uint8_t length = Create_Message_RESPONSE(dataout[2], RESPONSE_NACK, data);
                        USART1_Send_Data(data, length); // Gửi phản hồi NACK
        }

        break;
    }
    return length;
}

/**
 * @brief Kiểm tra xem đã nhận được một frame hoàn chỉnh và hợp lệ chưa.
 *
 * @return 1 nếu đã nhận đúng và đủ frame; 0 nếu chưa đủ hoặc không hợp lệ.
 */
uint8_t Check_Fsm_Flag_New_Message(void)
{
    return flag_fsm_new_message;
}
