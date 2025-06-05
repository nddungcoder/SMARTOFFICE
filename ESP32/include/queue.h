/*
 * queue.h
 *
 *  Created on: May 22, 2025
 *      Author: nguye
 */

#ifndef _QUEUE_H
#define _QUEUE_H

#include <stdint.h>
#include <stdbool.h>
#include "message.h"

// Sức chứa tối đa của hàng đợi (tính theo số lượng khung dữ liệu)
#define FRAME_QUEUE_CAPACITY 20

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Union dùng để truy cập khung dữ liệu dưới dạng cấu trúc hoặc mảng byte.
 */
typedef union {
    message_t frame;            ///< Dữ liệu khung dưới dạng cấu trúc message_t
    uint8_t data[FRAME_SIZE];   ///< Dữ liệu khung dưới dạng mảng byte
} Message_Convert_t;

/**
 * @brief Cấu trúc hàng đợi dùng để lưu trữ các khung dữ liệu.
 */
typedef struct {
    Message_Convert_t buffer[FRAME_QUEUE_CAPACITY]; ///< Bộ đệm chứa các khung dữ liệu
    int front;     ///< Vị trí phần tử đầu hàng đợi (sẽ được lấy ra đầu tiên)
    int rear;      ///< Vị trí phần tử cuối hàng đợi (vừa được thêm vào)
    int size;      ///< Số lượng phần tử hiện có trong hàng đợi
} FrameQueue;

/**
 * @brief Khởi tạo hàng đợi, thiết lập trạng thái ban đầu (rỗng).
 * @param q Con trỏ trỏ tới hàng đợi cần khởi tạo.
 */
void Queue_init(FrameQueue *q);

/**
 * @brief Thêm một khung dữ liệu vào cuối hàng đợi.
 * @param q Con trỏ trỏ tới hàng đợi.
 * @param frame Con trỏ tới khung dữ liệu cần thêm vào.
 * @param length Độ dài khung dữ liệu.
 * @return true nếu thêm thành công, false nếu hàng đợi đầy.
 */
bool push(FrameQueue *q, const message_t *frame, uint8_t length);

/**
 * @brief Loại bỏ phần tử đầu tiên khỏi hàng đợi.
 * @param q Con trỏ trỏ tới hàng đợi.
 * @return true nếu xóa thành công, false nếu hàng đợi rỗng.
 */
bool pop(FrameQueue *q);

/**
 * @brief Truy xuất phần tử đầu hàng đợi mà không xóa.
 * @param q Con trỏ trỏ tới hàng đợi.
 * @param dest Bộ đệm đích để sao chép dữ liệu.
 * @return true nếu truy xuất thành công, false nếu hàng đợi rỗng.
 */
bool front(FrameQueue *q, uint8_t *dest);

/**
 * @brief Truy xuất phần tử cuối hàng đợi (vừa thêm gần nhất).
 * @param q Con trỏ trỏ tới hàng đợi.
 * @param dest Bộ đệm đích để sao chép dữ liệu.
 * @return true nếu truy xuất thành công, false nếu hàng đợi rỗng.
 */
bool back(FrameQueue *q, uint8_t *dest);

/**
 * @brief Kiểm tra xem hàng đợi có đang rỗng không.
 * @param q Con trỏ trỏ tới hàng đợi.
 * @return true nếu rỗng, false nếu có phần tử.
 */
bool empty(const FrameQueue *q);

/**
 * @brief Kiểm tra xem hàng đợi đã đầy chưa.
 * @param q Con trỏ trỏ tới hàng đợi.
 * @return true nếu đầy, false nếu còn chỗ trống.
 */
bool full(const FrameQueue *q);

/**
 * @brief Lấy số lượng phần tử hiện tại trong hàng đợi.
 * @param q Con trỏ trỏ tới hàng đợi.
 * @return Số phần tử hiện có.
 */
int size(const FrameQueue *q);

#ifdef __cplusplus
}
#endif

#endif /* _QUEUE_H */
