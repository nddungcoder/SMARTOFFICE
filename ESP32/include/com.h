#ifndef __COM_H__
#define __COM_H__

#include "convert.h"
#include "fsm_message.h"
#include "fsm_trans.h"
#include "device_manager.h"
#include "queue.h"
#include "message.h"

/**
 * @brief Khởi tạo UART để giao tiếp.
 *
 * Cấu hình tốc độ baud cho UART và chuẩn bị cho quá trình truyền nhận dữ liệu.
 *
 * @param baud_rate Tốc độ baud mong muốn (mặc định là 9600).
 */
void COM_Init(uint32_t baud_rate = 9600);

/**
 * @brief Xử lý việc truyền dữ liệu qua UART.
 *
 * Gửi các khung dữ liệu từ hàng đợi. Có thể được gọi trong vòng lặp chính hoặc từ ISR.
 *
 * @param queue Hàng đợi chứa các khung dữ liệu cần gửi.
 */
void Transsmit_Handler(FrameQueue &queue);

/**
 * @brief Xử lý dữ liệu nhận được từ UART.
 *
 * Giải mã khung dữ liệu, phân tích thông điệp và cập nhật trạng thái thiết bị tương ứng.
 * Thường được gọi trong vòng lặp chính hoặc từ ISR (nếu thiết kế ngắt).
 *
 * @param device Đối tượng quản lý trạng thái thiết bị (sensor/actuator).
 * @param queue Hàng đợi lưu trữ các khung dữ liệu nhận được.
 */
void Receive_Handler(device_manager& device, FrameQueue& queue);

/**
 * @brief Gửi một gói dữ liệu qua UART.
 *
 * Gửi mảng dữ liệu theo dạng khung. Có thể tự động thêm byte bắt đầu nếu cần.
 *
 * @param data Con trỏ đến mảng dữ liệu cần gửi.
 * @param length Số byte cần gửi.
 * @param add_start Nếu khác 0, sẽ thêm byte bắt đầu (ví dụ 0xAA) vào đầu khung dữ liệu.
 */
void COM_Send_Data(const uint8_t *data, uint8_t length, uint8_t add_start);

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
