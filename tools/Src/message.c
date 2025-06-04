#include "message.h"
#include <string.h>

/**
 * @brief Kiểm tra dữ liệu
 */
uint16_t Message_Calculate_Checksum(const uint8_t *buf, uint8_t len)
{
    return 0xFFFF; // Todo: Implement checksum calculation
}

/**
 * @brief Tạo frame bản tin NOTIFY (truyền dữ liệu float từ cảm biến)
 */
uint8_t Create_Message_Notify(ID_t id, float value, uint8_t *dataout)
{
    if (dataout == NULL)
        return 0;

    uint8_t count = 0;

    dataout[count++] = START_BYTE;
    dataout[count++] = NOTIFY; // Group: NOTIFY
    dataout[count++] = id;     // ID thiết bị cảm biến (tùy chỉnh nếu cần)
    dataout[count++] = 4;      // Payload: 4 byte float

    // Chuyển float thành 4 byte Big-Endian
    uint8_t *pval = Convert_Float_To_Bytes(value);
    // Reverse byte order for Big-Endian
    for (int i = 0; i <= 3; i++)
    {
        dataout[count++] = pval[i];
    }

    // Calculate checksum
    uint16_t checksum = Message_Calculate_Checksum(dataout, count);

    // Write checksum in Big-Endian
    dataout[count++] = (checksum >> 8) & 0xFF; // High byte
    dataout[count++] = checksum & 0xFF;        // Low byte

    return count; // Trả về độ dài của Message
}

/**
 * @brief Tạo bản tin phản hồi (RESPONSE)
 */
uint8_t Create_Message_RESPONSE(ID_t id, RESPONSE_t r, uint8_t *dataout)
{
    if (dataout == NULL)
        return 0;

    uint8_t count = 0;
    dataout[count++] = START_BYTE;
    dataout[count++] = RESPONSE;   // Group: RESPONSE
    dataout[count++] = id;         // ID thiết bị phản hồi (tùy chỉnh nếu cần)
    dataout[count++] = 1;          // Payload chỉ 1 byte phản hồi
    dataout[count++] = (uint8_t)r; // Phản hồi
    // Calculate checksum
    uint16_t checksum = Message_Calculate_Checksum(dataout, count);
    // Write checksum in Big-Endian
    dataout[count++] = (checksum >> 8) & 0xFF; // High byte
    dataout[count++] = checksum & 0xFF;        // Low byte
    return count;                              // Trả về độ dài của Message
}

/**
 * @brief Giải mã frame nhận được
 */
bool Message_Decode(const uint8_t *buffer, message_t *frame_out)
{
    if (buffer == NULL || frame_out == NULL)
        return false;

    if (buffer[0] != START_BYTE)
        return false;

    frame_out->start = buffer[0];
    memcpy(frame_out->header, &buffer[1], HEADER_SIZE);
    uint8_t payload_len = frame_out->header[2];

    if (payload_len > PAYLOAD_SIZE)
        return false;

    memcpy(frame_out->payload, &buffer[1 + HEADER_SIZE], payload_len);

    uint8_t temp[HEADER_SIZE + PAYLOAD_SIZE];
    memcpy(temp, frame_out->header, HEADER_SIZE);
    memcpy(temp + HEADER_SIZE, frame_out->payload, payload_len);

    uint16_t received_checksum = buffer[1 + HEADER_SIZE + payload_len] |
                                 (buffer[1 + HEADER_SIZE + payload_len + 1] << 8);
    uint16_t calc_checksum = Message_Calculate_Checksum(temp, HEADER_SIZE + payload_len);

    if (received_checksum != calc_checksum)
        return false;

    frame_out->checksum = received_checksum;
    return true;
}

bool Check_Frame_Header(const uint8_t headerframe[])
{
   if (headerframe[0] != COMMAND && headerframe[0] == RESPONSE && headerframe[0] == NOTIFY)
       return false;
   if (headerframe[1] != CDS && headerframe[1] != IR && headerframe[1] != MQ2 && headerframe[1] != DHT11_HUMI && headerframe[1] != DHT11_TEMP &&
       headerframe[1] != LED && headerframe[1] != MOTOR && headerframe[1] != SIREN && headerframe[1] != AUTO && headerframe[1] != UNKNOWN)
       return false;
   if (headerframe[2] > PAYLOAD_SIZE)
       return false; // Kiểm tra độ dài payload

   return true;

	
}
