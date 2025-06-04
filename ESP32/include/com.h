#ifndef __COM_H__
#define __COM_H__

#include "convert.h"
#include "fsm_message.h"
#include "device_manager.h"
#include "queue.h"

/**
 * @brief Khởi tạo UART để giao tiếp.
 *
 * Cấu hình tốc độ baud cho UART và chuẩn bị cho quá trình truyền nhận dữ liệu.
 *
 * @param baud_rate Tốc độ baud mong muốn (mặc định là 9600).
 */
void COM_Init(uint32_t baud_rate = 9600);

/**
 * @brief task xử lý truyền dữ liệu qua UART.
 *
 * Hàm này liên tục lấy dữ liệu từ hàng đợi truyền và gửi qua UART.
 * Được sử dụng trong môi trường FreeRTOS như một task độc lập.
 *
 * @param param Con trỏ tới tham số khởi tạo task (thường là NULL hoặc cấu trúc cấu hình).
 */
void uart_tx_task(void *param);

/**
 * @brief Task xử lý sự kiện UART như nhận dữ liệu, lỗi, hoặc ngắt.
 *
 * Hàm này bắt sự kiện từ driver UART (qua queue sự kiện),
 * xử lý dữ liệu đến và thực hiện các hành động tương ứng như phân tích khung dữ liệu hoặc phản hồi.
 *
 * @param pvParameters Con trỏ tới tham số khởi tạo task (thường là NULL hoặc con trỏ tới cấu trúc cần thiết).
 */
void uart_event_task(void *pvParameters);


/**
 * @brief Xử lý thông điệp thông báo từ thiết bị.
 *
 * Phân tích và cập nhật giá trị của các cảm biến hoặc thiết bị dựa trên thông điệp nhận được.
 *
 * @param device Đối tượng quản lý trạng thái thiết bị (sensor/actuator).
 */
void COM_HandleNotifyMessage(device_manager &device);


/**
 * @brief Xử lý thông điệp phản hồi từ thiết bị.
 *
 * Phân tích và xử lý các thông điệp phản hồi từ thiết bị, thường là kết quả của các lệnh đã gửi.
 *
 * @param queue Hàng đợi chứa các khung dữ liệu phản hồi.
 */
void COM_HandleResponseMessage(FrameQueue &queue);

#endif  // __COM_H__
