#ifndef _FSM_TRANS_H
#define _FSM_TRANS_H

#include "message.h"
#include <stdio.h>

typedef enum {
    TRANS_STATE_START = 1,    ///< Trạng thái bắt đầu - chờ byte START_BYTE
    TRANS_STATE_HEADER = 2,   ///< Trạng thái nhận header (group, id, length)
    TRANS_STATE_PAYLOAD = 3,  ///< Trạng thái gửi dữ liệu payload
    TRANS_STATE_CHECKSUM = 4  ///< Trạng thái gửi checksum
} trans_state_t;

/**
 * @brief Xóa tất cả trạng thái của FSM.
 * 
 * Hàm này sẽ đặt lại tất cả các biến trạng thái của FSM về giá trị ban đầu,
 * bao gồm trạng thái, bộ đếm byte, độ dài payload mong đợi, và cờ đã gửi xong.
 */
void Clear_All_State_Trans(void);


/**
 * @brief Xử lý trạng thái FSM để gửi frame message.
 * 
 * Hàm này sẽ được gọi khi có dữ liệu mới cần gửi. Nó sẽ kiểm tra trạng thái
 * hiện tại của FSM và thực hiện các bước cần thiết để gửi frame message.
 * 
 * @param response Phản hồi từ bên nhận.
 * @param message Con trỏ tới dữ liệu cần gửi.
 */
void Fsm_Trans_Message(RESPONSE_t response, frame_message_t* message);

/**
 * @brief Kiểm tra xem đã gửi được một frame hoàn chỉnh và hợp lệ chưa.
 * 
 * Hàm này sẽ kiểm tra cờ trạng thái để xác định xem đã nhận đúng và đủ frame
 * hay chưa. Nếu đã nhận xong, nó sẽ trả về 1, ngược lại trả về 0.
 * 
 * @return 1 nếu đã gửi đúng và đủ frame; 0 nếu chưa đủ hoặc không hợp lệ.
 */
uint8_t Check_Flag_Trans_New_Message(void);

/**
 * @brief Trả về trạng thái hiện tại của FSM.
 * 
 * Hàm này sẽ trả về trạng thái hiện tại của FSM, có thể là START, HEADER,
 * PAYLOAD hoặc CHECKSUM.
 * 
 * @return Trạng thái hiện tại của
 */
trans_state_t Frame_To_Trans(void);


/**
 * @brief Trả về trạng thái của slave.
 * 
 * Hàm này sẽ trả về trạng thái hiện tại của slave, có thể là RESPONSE_READY,
 * RESPONSE_BUSY, RESPONSE_ACK hoặc RESPONSE_NACK.
 * 
 * @return Trạng thái hiện tại của slave.
 */
RESPONSE_t Get_Slave_State(void);


#endif