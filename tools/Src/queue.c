#include "queue.h"
#include <string.h>

void init(FrameQueue *q) {
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

bool push(FrameQueue *q, const Frame *f) {
    if (full(q)) return false;

    q->rear = (q->rear + 1) % FRAME_QUEUE_CAPACITY;
    memcpy(&q->buffer[q->rear], f, sizeof(Frame));
    q->size++;
    return true;
}

bool pop(FrameQueue *q) {
    if (empty(q)) return false;

    q->front = (q->front + 1) % FRAME_QUEUE_CAPACITY;
    q->size--;
    return true;
}

Frame* front(const FrameQueue *q) {
    if (empty(q)) return NULL;
    return (Frame*)&q->buffer[q->front];
}

Frame* back(const FrameQueue *q) {
    if (empty(q)) return NULL;
    return (Frame*)&q->buffer[q->rear];
}
