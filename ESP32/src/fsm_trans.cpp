#include "fsm_trans.h"
#include "string.h"

static RESPONSE_t slave_state = RESPONSE_READY;
static trans_state_t fsm_state = TRANS_STATE_START;
static uint8_t flag_fsm_new_message = 0;

static trans_state_t Next_Trans_State(trans_state_t current_state);

/**
 * @brief Đặt lại FSM về trạng thái ban đầu.
 *
 * Hàm này sẽ xóa cờ trạng thái và đưa FSM
 * về trạng thái sẵn sàng nhận frame mới từ đầu.
 */
void Clear_All_State_Trans(void)
{
    slave_state = RESPONSE_READY;
    fsm_state = TRANS_STATE_START;
    flag_fsm_new_message = 0;
}

/**
 * @brief Xử lý trạng thái FSM để gửi frame message.
 *
 * Hàm này sẽ được gọi khi có dữ liệu mới cần gửi. Nó sẽ kiểm tra trạng thái
 * hiện tại của FSM và thực hiện các bước cần thiết để gửi frame message.
 *
 * @param response Phản hồi từ thiết bị khác (nếu có).
 * @param message Con trỏ tới dữ liệu cần gửi.
 */
void Fsm_Trans_Message(RESPONSE_t response, frame_message_t *message)
{
    if (flag_fsm_new_message)
        return;

    if(slave_state == RESPONSE_BUSY && response != RESPONSE_READY)
    {
        return; // Nếu đang bận và không phải là READY, không làm gì cả
    }

    switch (response)
    {
    case RESPONSE_READY:
        Clear_All_State_Trans();
        break;
    case RESPONSE_BUSY:
        slave_state = RESPONSE_BUSY; // Đặt trạng thái là BUSY
        if (fsm_state == TRANS_STATE_CHECKSUM)
        {
            fsm_state = Next_Trans_State(fsm_state); 
            flag_fsm_new_message = 1; // Đặt cờ để báo đã gửi xong frame
        }
        break;
    case RESPONSE_ACK:
        slave_state = RESPONSE_ACK; 
        if(fsm_state == TRANS_STATE_CHECKSUM) 
        {
            flag_fsm_new_message = 1; 
        }
        fsm_state = Next_Trans_State(fsm_state);
        break;                      
    case RESPONSE_NACK:
        slave_state = RESPONSE_NACK; 
        break;              
    }
}

/**
 * @brief Kiểm tra xem đã gửi được một frame hoàn chỉnh và hợp lệ chưa.
 *
 * @return 1 nếu đã nhận đúng và đủ frame; 0 nếu chưa đủ hoặc không hợp lệ.
 */
uint8_t Check_Flag_Trans_New_Message(void)
{
    return flag_fsm_new_message;
}

trans_state_t Frame_To_Trans(void)
{
    return fsm_state;
}

RESPONSE_t Get_Slave_State(void)
{
    return slave_state;
}

static trans_state_t Next_Trans_State(trans_state_t current_state) {
    switch (current_state) {
        case TRANS_STATE_START:
            return TRANS_STATE_HEADER;
        case TRANS_STATE_HEADER:
            return TRANS_STATE_PAYLOAD;
        case TRANS_STATE_PAYLOAD:
            return TRANS_STATE_CHECKSUM;
        case TRANS_STATE_CHECKSUM:
        default:
            return TRANS_STATE_START; // Quay về START sau CHECKSUM
    }
}