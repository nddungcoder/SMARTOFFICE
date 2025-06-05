#ifndef MESSAGE_H
#define MESSAGE_H

#include <convert.h>
#include <stdbool.h>

#define START_BYTE 0xAA
#define HEADER_SIZE 3
#define PAYLOAD_SIZE 4
#define CHECKSUM_SIZE 2
#define FRAME_SIZE 10

// Cấu trúc frame dữ liệu
typedef struct
{
    uint8_t start;                 // 1 byte: START_BYTE = 0xAA
    uint8_t header[HEADER_SIZE];   // 3 byte: GROUP (1Byte) + ID (1Byte) + Length(1Byte)
    uint8_t payload[PAYLOAD_SIZE]; // N byte: dữ liệu
    uint16_t checksum;
} message_t;

typedef enum
{
    COMMAND = 0X01,
    RESPONSE = 0X02,
    NOTIFY = 0X03
} Group_t;

typedef enum
{
    CDS = 0x01,
    IR = 0x02,
    MQ2 = 0x03,
    DHT11_HUMI = 0x04,
    DHT11_TEMP = 0x05,
    LED = 0x11,
    MOTOR = 0x12,
    SIREN = 0x13,
    AUTO = 0x20,
    UNKNOWN = 0xFF, // ID không xác định, dùng để phản hồi khi có lỗi
} ID_t;

typedef enum
{
    RESPONSE_ACK = 0x01,
    RESPONSE_NACK = 0x02,
    RESPONSE_BUSY = 0x03,
    RESPONSE_READY = 0x04,
} RESPONSE_t;

// ==== Prototype của các hàm xử lý frame ====

/**
 * @brief Tạo gói tin dạng COMMAND từ một giá trị float và ID thiết bị.
 *
 * Hàm này sẽ chuyển đổi giá trị float thành 4 byte, sau đó đóng gói thành một
 * gói tin command phù hợp với định dạng giao tiếp đã thiết kế.
 * Kết quả được lưu vào mảng `dataout`.
 *
 * @param id       ID_t của thiết bị cần gửi lệnh (ví dụ: LED, MOTOR, DHT11...).
 * @param value    Giá trị dạng float cần gửi đi (ví dụ: tốc độ motor, ngưỡng sensor...).
 * @param dataout  Con trỏ đến mảng byte để lưu gói tin đã được tạo (phải đủ dung lượng).
 *
 * @return Số byte của gói tin đã tạo (độ dài thực tế của frame).
 */
void Create_Message_COMMAND(ID_t id, float value, message_t* messageout);

/**
 * @brief Tạo frame dữ liệu phản hồi
 * @param response: phản hồi
 * @param frame_out: mảng chứa frame tạo ra
 * @return độ dài frame
 */
uint8_t Create_Message_RESPONSE(ID_t id, RESPONSE_t r, uint8_t *dataout);

/**
 * @brief Phân tích frame đầu vào từ buffer
 * @param buffer: dữ liệu thô
 * @param frame_out: nơi lưu kết quả
 * @return true nếu hợp lệ
 */
bool Message_Decode(const uint8_t *buffer, message_t *dataout);

/**
 * @brief Tính tổng kiểm tra
 * @param buf: buffer
 * @param len: độ dài tính
 * @return giá trị checksum (2 byte)
 */
uint16_t Message_Calculate_Checksum(const uint8_t *buf, uint8_t len);

#endif
