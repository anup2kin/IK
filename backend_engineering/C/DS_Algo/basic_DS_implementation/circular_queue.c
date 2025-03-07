#include <stdio.h>
#include <stdlib.h>

typedef struct CircularQueue{
    int *buf;
    int headIdx;
    int tailIdx;
    int size;
    int capacity;
} CircularQueue;

void init_circular_queue(CircularQueue *q, int size){
    q->buf = (int *) malloc (sizeof(int) * size);
    q->capacity = size;
    q->size = 0;
    q->headIdx = -1;
    q->tailIdx = -1;
}

void push(CircularQueue *q, int value, int *isFull){
    *isFull = 0;

    if(q->size == q->capacity){
        *isFull = 1;
        return;
    }

    if(q->size == 0){
        q->headIdx = 0;
        q->tailIdx = 0;
    }
    else{
        q->tailIdx = ((q->tailIdx + 1) % q->capacity);
    }
    
    q->buf[q->tailIdx] = value;
    ++q->size;
}

int pop(CircularQueue *q, int *isEmpty){
    *isEmpty = 0;

    if(q->size == 0){
        *isEmpty = 1;
        return -1;
    }

    int poppedValue = q->buf[q->headIdx];
    --q->size;

    if(q->size == 0){
        q->headIdx = -1;
        q->tailIdx =  -1;
    }
    else{
         q->headIdx =(q->headIdx + 1) % q->capacity;
    }

    return poppedValue;
}

void free_circular_queue(CircularQueue *q){
    free(q->buf);
    q->buf = NULL;
    q->headIdx = -1;
    q->tailIdx = -1;
    q->size = 0;
    q->capacity = 0;
}

int main() {
    CircularQueue myQueue;
    int isFull, isEmpty, poppedValue;

    init_circular_queue(&myQueue, 5);

    push(&myQueue, 10, &isFull);
    push(&myQueue, 20, &isFull);
    push(&myQueue, 30, &isFull);
    push(&myQueue, 40, &isFull);
    push(&myQueue, 50, &isFull);

    push(&myQueue, 60, &isFull); // Should be full, isFull will be 1.

    if (isFull) {
        printf("Queue is full.\n");
    }

    while (1) {
        poppedValue = pop(&myQueue, &isEmpty);
        if (isEmpty) {
            break;
        }
        printf("Popped: %d\n", poppedValue);
    }

    free_circular_queue(&myQueue);
    return 0;
}