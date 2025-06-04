#include "queue.h"
#include <string.h>

void Queue_init(FrameQueue *q) {
    q->front = 0;
    q->rear = -1;
    q->size = 0;
}

bool empty(const FrameQueue *q) {
    return q->size == 0;
}

bool full(const FrameQueue *q) {
    return q->size == FRAME_QUEUE_CAPACITY;
}

int size(const FrameQueue *q) {
    return q->size;
}

bool push(FrameQueue *q, const message_t frame, uint8_t length) {
    if (full(q)) return false;

    q->buffer[q->rear].frame = frame; // copy kiểu struct đơn giản
    q->rear = (q->rear + 1) % FRAME_QUEUE_CAPACITY;
    q->size++;
    return true;
}

bool pop(FrameQueue *q) {
    if (empty(q)) return false;

    q->front = (q->front + 1) % FRAME_QUEUE_CAPACITY;
    q->size--;
    return true;
}

Message_Convert_t front(const FrameQueue *q) {
    Message_Convert_t dummy = {0}; // Trả về giá trị rỗng nếu hàng đợi trống
    if (empty(q)) return dummy;

    return q->buffer[q->front]; 
}

Message_Convert_t back(const FrameQueue *q) {
    Message_Convert_t dummy = {0}; // Trả về giá trị rỗng nếu hàng đợi trống
    if (empty(q)) return dummy;

    int index = (q->rear - 1 + FRAME_QUEUE_CAPACITY) % FRAME_QUEUE_CAPACITY;
    return q->buffer[index]; // Trả bản sao phần tử cuối
}
