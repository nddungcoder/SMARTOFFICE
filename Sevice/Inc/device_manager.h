#ifndef NOTIFY_H
#define NOTIFY_H

#include <stdint.h>


/**
 * Khởi tạo các thiết bị và cảm biến.
 * Bao gồm: DHT11, CDS, MQ2, LED RGB, Motor, Siren,...
 */
void device_init(void);


/**
 * Cập nhật dữ liệu từ các cảm biến và thiết bị.
 * Gửi lên hệ thống nếu có thay đổi.
 */
void DeviceManager_UpdateData(void);



#endif // NOTIFY_H
