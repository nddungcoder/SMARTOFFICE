/*
 * queue
 *
 *  Created on: May 22, 2025
 *      Author: nguye
 */

#ifndef INC_QUEUE_
#define INC_QUEUE_

#include <stdint.h>
#include <stdbool.h>

// Kích thước một khung dữ liệu (frame) tính theo byte
#define FRAME_SIZE 10

// Sức chứa tối đa của hàng đợi (số lượng frame)
#define FRAME_QUEUE_CAPACITY 20

#ifdef __cplusplus
extern "C" {
#endif

// Cấu trúc đại diện cho một khung dữ liệu
typedef struct {
    uint8_t data[FRAME_SIZE];  // Mảng byte chứa nội dung khung
} Frame;

// Cấu trúc hàng đợi lưu trữ các khung dữ liệu
typedef struct {
    Frame buffer[FRAME_QUEUE_CAPACITY]; // Bộ đệm chứa các khung
    int front;     // Vị trí đầu hàng đợi (frame sắp được lấy ra)
    int rear;      // Vị trí cuối hàng đợi (frame mới được thêm vào)
    int size;      // Số lượng phần tử hiện có trong hàng đợi
} FrameQueue;

// Khởi tạo hàng đợi (đặt về trạng thái rỗng)
void init(FrameQueue *q);

// Thêm một khung dữ liệu vào cuối hàng đợi (enqueue)
bool push(FrameQueue *q, const Frame *f);

// Xóa một khung dữ liệu ở đầu hàng đợi (dequeue)
bool pop(FrameQueue *q);

// Truy xuất khung dữ liệu ở đầu hàng đợi (không xóa)
Frame* front(const FrameQueue *q);

// Truy xuất khung dữ liệu được thêm gần nhất (cuối hàng đợi)
Frame* back(const FrameQueue *q);

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
