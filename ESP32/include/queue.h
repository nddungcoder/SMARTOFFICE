/*
 * queue
 *
 *  Created on: May 22, 2025
 *      Author: nguye
 */

#ifndef _QUEUE_H
#define _QUEUE_H

#include <stdint.h>
#include <stdbool.h>
#include "message.h"

// Sức chứa tối đa của hàng đợi (số lượng frame)
#define FRAME_QUEUE_CAPACITY 20

#ifdef __cplusplus
extern "C" {
#endif

// Cấu trúc hàng đợi lưu trữ các khung dữ liệu
typedef struct {
    frame_message_t buffer[FRAME_QUEUE_CAPACITY]; // Bộ đệm chứa các khung
    int front;     // Vị trí đầu hàng đợi (frame sắp được lấy ra)
    int rear;      // Vị trí cuối hàng đợi (frame mới được thêm vào)
    int size;      // Số lượng phần tử hiện có trong hàng đợi
} FrameQueue;

// Khởi tạo hàng đợi (đặt về trạng thái rỗng)
void Queue_init(FrameQueue *q);

// Thêm một khung dữ liệu vào cuối hàng đợi (enqueue)
bool push(FrameQueue *q, const frame_message_t f, uint8_t length);

// Xóa một khung dữ liệu ở đầu hàng đợi (dequeue)
bool pop(FrameQueue *q);

// Truy xuất khung dữ liệu ở đầu hàng đợi (không xóa)
frame_message_t* front(const FrameQueue *q);

// Truy xuất khung dữ liệu được thêm gần nhất (cuối hàng đợi)
frame_message_t* back(const FrameQueue *q);

// Kiểm tra xem hàng đợi có rỗng hay không
bool empty(const FrameQueue *q);

// Kiểm tra xem hàng đợi đã đầy hay chưa
bool full(const FrameQueue *q);

// Trả về số lượng phần tử hiện có trong hàng đợi
int size(const FrameQueue *q);

#ifdef __cplusplus
}
#endif

#endif /* INC_QUEUE_ */
