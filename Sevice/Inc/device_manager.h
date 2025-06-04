#ifndef NOTIFY_H
#define NOTIFY_H

#include <stdint.h>


/**
 * Khởi tạo các thiết bị và cảm biến.
 * Bao gồm: DHT11, CDS, MQ2, LED RGB, Motor, Siren,...
 */
void device_init(void);

/**
 * @brief Đọc toàn bộ dữ liệu hệ thống và gửi qua UART.
 * Bao gồm cảm biến, LED RGB, motor,...
 */
void READ_Sensor(void);

/**
 * @brief Gửi một thông báo.
 */
void Notify_SendMessage(void);



#endif // NOTIFY_H
