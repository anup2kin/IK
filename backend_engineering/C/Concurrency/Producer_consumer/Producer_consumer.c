#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<stdbool.h>
#include<unistd.h>

typedef struct CircularQueue{
    int *buffer;
    int headIdx;
    int tailIdx;
    int size;
    int capacity;
} CircularQueue;

void initCircularQueue(CircularQueue *q, int capacity){
    q->capacity = capacity;
    q->buffer = (int*)malloc(sizeof(int) * capacity);
    q->headIdx = -1;
    q->tailIdx = -1;
    q->size = 0;
}

bool isEmpty(CircularQueue *q){
    if(q->size == 0) return true;
    else return false;
}

bool isFull(CircularQueue *q){
    if(q->size == q->capacity) return true;
    else return false;
}

void push(CircularQueue *q, int val){
    if(isFull(q) == true) return;

    if(q->size == 0){
        q->headIdx = 0;
        q->tailIdx = 0;
    }
    else{
        q->tailIdx = (q->tailIdx + 1) % q->capacity;
    }
    printf("[DEBUG] Pushed %d at index %d\n", val, q->tailIdx);
    q->buffer[q->tailIdx] = val;
    ++q->size;
}

int pop(CircularQueue *q){
    if(isEmpty(q) == true) return -1;
    
    int poppedValue = q->buffer[q->headIdx];
    printf("[DEBUG] Popped %d from index %d\n", poppedValue, q->headIdx);
    --q->size;
    if(q->size == 0){
        q->headIdx = -1;
        q->tailIdx = -1;
    }
    else{
        q->headIdx = (q->headIdx + 1) % q->capacity;
    }

    return poppedValue;
}

// Global variables
int activeProducers;  // Tracks active producers
pthread_mutex_t mtx;
pthread_cond_t cv;
CircularQueue q;

void* producer(void *args){
    int *producerId = (int*)args;

   for(int i = 0; i < 20; i++){
        pthread_mutex_lock(&mtx);

        while(isFull(&q) == true){
            pthread_cond_wait(&cv, &mtx);
        }

        printf("[%d] Producing [%d]\n", *producerId, i);
        push(&q, i);

        pthread_cond_signal(&cv);
        pthread_mutex_unlock(&mtx);
    }

    // Mark producer as done
    pthread_mutex_lock(&mtx);
    activeProducers--;
    if (activeProducers == 0) {
        pthread_cond_broadcast(&cv);  // Wake up all consumers to check for termination
    }
    pthread_mutex_unlock(&mtx);

    return NULL;
}

void* consumer(void *args){
    int *consumerId = (int*)args;

    while(true){
        pthread_mutex_lock(&mtx);

       while (isEmpty(&q) && activeProducers > 0) {
            pthread_cond_wait(&cv, &mtx);
        }

        if (isEmpty(&q) && activeProducers == 0) {
            pthread_mutex_unlock(&mtx);
            return NULL;
        }

        int val = pop(&q);
        printf("[Consumer %d] Consuming %d\n", *consumerId, val);

        pthread_cond_broadcast(&cv);
        pthread_mutex_unlock(&mtx);
        usleep(100000);
    }
}


// Main Function
int main() {
    int numProducers = 2;
    int numConsumers = 2;
    activeProducers = numProducers;  // Set the number of active producers
    
    pthread_mutex_init(&mtx, NULL);
    pthread_cond_init(&cv, NULL);

    initCircularQueue(&q, 5);

    pthread_t producers[numProducers], consumers[numConsumers];
    int producerIds[numProducers], consumerIds[numConsumers];

    // Creating producer threads
    for (int i = 0; i < numProducers; i++) {
        producerIds[i] = i + 1;
        pthread_create(&producers[i], NULL, producer, &producerIds[i]);
    }

    // Creating consumer threads
    for (int i = 0; i < numConsumers; i++) {
        consumerIds[i] = i + 1;
        pthread_create(&consumers[i], NULL, consumer, &consumerIds[i]);
    }

    // Joining producer threads
    for (int i = 0; i < numProducers; i++) {
        pthread_join(producers[i], NULL);
    }

    // Joining consumer threads
    for (int i = 0; i < numConsumers; i++) {
        pthread_join(consumers[i], NULL);
    }

    // Cleanup
    free(q.buffer);
    pthread_mutex_destroy(&mtx);
    pthread_cond_destroy(&cv);

    printf("All tasks completed successfully.\n");
    return 0;
}