#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<pthread.h>
#include<unistd.h>


typedef struct TaskNode{
    bool quitTask;
    void *args;
    void (*run)(void *args);
    struct TaskNode *prev;
    struct TaskNode *next;
} TaskNode;

TaskNode* createTaskNode(void *args, void (*run) (void *args), bool isQuit){
    TaskNode *node = (TaskNode*)malloc(sizeof(TaskNode));
    if (!node) {
        perror("malloc failed");
        exit(EXIT_FAILURE);
    }
    node->quitTask = isQuit;
    node->args = args;
    node->run = run;
    node->prev = NULL;
    node->next = NULL;
    return node;
}

void freeTaskNode(TaskNode *node){
    free(node);
}

typedef struct ConcurrentQueue{
    TaskNode *head;
    TaskNode *tail;
    pthread_mutex_t mtx;
    pthread_cond_t cv;

} ConcurrentQueue;

void initConcurrentQueue(ConcurrentQueue *q){
    q->head = NULL;
    q->tail = NULL;
    pthread_mutex_init(&q->mtx, NULL);
    pthread_cond_init(&q->cv, NULL);
}

void push(ConcurrentQueue *q, void *args, void (*run) (void *args), bool quitTask){
    pthread_mutex_lock(&q->mtx);

    TaskNode *task = createTaskNode(args, run, quitTask);

    if(q->head == NULL){
        q->head = task;
        q->tail = task;
    }
    else{
        q->tail->next = task;
        task->prev = q->tail;
        q->tail = task;
    }

    pthread_cond_signal(&q->cv);
    pthread_mutex_unlock(&q->mtx);
}

TaskNode* pop(ConcurrentQueue *q){
    pthread_mutex_lock(&q->mtx);

    while (q->head == NULL) {  // Avoid spurious wakeups
        pthread_cond_wait(&q->cv, &q->mtx);
    }

    TaskNode *poppedTask = q->head;
    q->head = q->head->next;
    if (q->head == NULL) {
        q->tail = NULL;
    }

    pthread_mutex_unlock(&q->mtx);
    return poppedTask;
}

typedef struct ThreadPool{
    pthread_t *threads;
    int numThreads;
    ConcurrentQueue q;
} ThreadPool;

void* worker(void *args){
    ThreadPool *tp = (ThreadPool*)args;
    while (true) {
        TaskNode *task = pop(&tp->q);
        if (task->quitTask) {
            freeTaskNode(task);
            return NULL;  // Thread exits
        }
        task->run(task->args);
        freeTaskNode(task);
    }
}

void initThreadPool(ThreadPool *tp, int numThreads){
    initConcurrentQueue(&tp->q);
    tp->numThreads = numThreads;
    tp->threads = (pthread_t*)malloc(sizeof(pthread_t) * numThreads);
    
    if (!tp->threads) {
        perror("malloc failed");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < tp->numThreads; i++) {
        pthread_create(&tp->threads[i], NULL, worker, tp);
    }
}

void addWork(ThreadPool *tp, void (*run)(void *args), void *args){
    push(&tp->q, args, run, false);
}

void destroyPool(ThreadPool *tp){
    // Push "shutdown" tasks equal to the number of threads
    for (int i = 0; i < tp->numThreads; i++) {
        push(&tp->q, NULL, NULL, true);
    }

    // Wait for all threads to finish
    for (int i = 0; i < tp->numThreads; i++) {
        pthread_join(tp->threads[i], NULL);
    }

    // Cleanup remaining tasks in queue
    pthread_mutex_lock(&tp->q.mtx);
    while (tp->q.head != NULL) {
        TaskNode *temp = tp->q.head;
        tp->q.head = tp->q.head->next;
        freeTaskNode(temp);
    }
    tp->q.tail = NULL;
    pthread_mutex_unlock(&tp->q.mtx);

    // Free thread memory and destroy synchronization primitives
    free(tp->threads);
    tp->threads = NULL;
    pthread_mutex_destroy(&tp->q.mtx);
    pthread_cond_destroy(&tp->q.cv);
}


// Sample task function
void printTask(void *arg) {
    int *num = (int*)arg;
    printf("Thread %ld processing task: %d\n", pthread_self(), *num);
    sleep(1); // Simulate work
}

int main() {
    // Step 1: Initialize ThreadPool
    int numThreads = 4;
    ThreadPool pool;
    initThreadPool(&pool, numThreads);

    // Step 2: Add tasks to the pool
    for (int i = 0; i < 10; i++) {
        int *taskNum = (int*)malloc(sizeof(int));
        *taskNum = i + 1;
        addWork(&pool, printTask, taskNum);
    }

    // Step 3: Wait a bit before shutting down (simulate workload)
    sleep(5);

    // Step 4: Destroy the pool
    destroyPool(&pool);

    printf("All tasks completed. Thread pool destroyed.\n");
    return 0;
}
