#ifndef __LIB_MESSAGE_H
#define __LIB_MESSAGE_H
#include <convert.h>

#define START_BYTE                  0xAA         // Byte bắt đầu frame
#define MAX_PAYLOAD_SIZE           12           // Số byte dữ liệu payload tối đa
#define CHECKSUM_SIZE              2            // Số byte CRC 

#define FRAME_OVERHEAD             (1 + 3  + 2) // Start + Header + Checksum

// Cấu trúc frame dữ liệu
typedef struct {
    uint8_t  start;                          // 1 byte: START_BYTE = 0xAA
    uint8_t  header[Header_Size];            // 3 byte: Type message (1Byte) + Device (1Byte) + Length(1Byte)
    uint8_t  payload[MAX_PAYLOAD_SIZE];      // N byte: dữ liệu
    uint16_t checksum;                       // 2 byte: CRC hoặc tổng kiểm tra
} frame_message_t;

// Enum định nghĩa loại message
typedef enum {
    MSG_TYPE_SET_PORT        = 0x01,
    MSG_TYPE_CONFIRM_PORT    = 0x02,
    MSG_TYPE_ASK_SENSOR      = 0x03,
    MSG_TYPE_RESPOND_SENSOR  = 0x04
} message_type_t;

// Enum định nghĩa các cổng
typedef enum {
    PORT_A = 0x01,
    PORT_B = 0x02
} port_t;

// Enum định nghĩa mã ngoại vi
typedef enum {
    SENSOR_CDS  = 0x01,
    SENSOR_  = 0x02,
    SENSOR_NTC  = 0x03,
    SENSOR_RES  = 0x04
} device_code_t;

// ==== Prototype của các hàm xử lý frame ====

/**
 * @brief Tạo frame dữ liệu từ cổng và giá trị
 * @param port: cổng dữ liệu
 * @param value: giá trị cần gửi
 * @param frame_out: mảng chứa frame tạo ra
 * @return độ dài frame
 */
uint8_t Message_Create(uint8_t port, float value, uint8_t *frame_out);

/**
 * @brief Giải mã dữ liệu từ frame đầu vào
 */
float Message_Get_Value(const frame_message_t *frame_in);

/**
 * @brief Phân tích frame đầu vào từ buffer
 * @param buffer: dữ liệu thô
 * @param frame_out: nơi lưu kết quả
 * @return true nếu hợp lệ
 */
bool Message_Decode_Frame(const uint8_t *buffer, frame_message_t *frame_out);

/**
 * @brief Tính tổng kiểm tra
 * @param buf: buffer
 * @param len: độ dài tính
 * @return giá trị checksum (2 byte)
 */
uint16_t Message_Calculate_Checksum(const uint8_t *buf, uint8_t len);