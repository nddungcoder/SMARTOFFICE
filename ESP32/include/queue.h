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

typedef union {
    message_t frame;                      
    uint8_t data[FRAME_SIZE];               
} Message_Convert_t;


typedef struct {
    Message_Convert_t buffer[FRAME_QUEUE_CAPACITY]; 
    int front;     // Vị trí đầu hàng đợi (frame sắp được lấy ra)
    int rear;      // Vị trí cuối hàng đợi (frame mới được thêm vào)
    int size;      // Số lượng phần tử hiện có trong hàng đợi
} FrameQueue;

// Khởi tạo hàng đợi (đặt về trạng thái rỗng)
void Queue_init(FrameQueue *q);

// Thêm một khung dữ liệu vào cuối hàng đợi (enqueue)
bool push(FrameQueue *q, const message_t frame, uint8_t length);

// Xóa một khung dữ liệu ở đầu hàng đợi (dequeue)
bool pop(FrameQueue *q);

// Truy xuất khung dữ liệu ở đầu hàng đợi (không xóa)
Message_Convert_t front(const FrameQueue *q);

// Truy xuất khung dữ liệu được thêm gần nhất (cuối hàng đợi)
Message_Convert_t back(const FrameQueue *q);

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
