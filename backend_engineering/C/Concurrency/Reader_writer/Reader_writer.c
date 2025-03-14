#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<unistd.h>
#include<stdbool.h>

#define NUM_READERS 4
#define NUM_WRITERS 4

pthread_rwlock_t sharedMtx;
pthread_mutex_t quitMtx;
int sharedData = 0;
bool QuitFlag = false;

void* reader(void *args){
    int readerId = *(int*)args;
    free(args);
    while(true){
        pthread_rwlock_rdlock(&sharedMtx);

        printf("[%d] Reader reading [%d]\n", readerId, sharedData);

        pthread_mutex_lock(&quitMtx);
        bool quit = QuitFlag;
        pthread_mutex_unlock(&quitMtx);

        pthread_rwlock_unlock(&sharedMtx);

        if(quit == true) return NULL;
        usleep(100000);
    }
}

void* writer(void *args){
    int writerId = *(int*)args;
    free(args);
    while(true){
        pthread_rwlock_wrlock(&sharedMtx);

        if(sharedData == 20){
            pthread_mutex_lock(&quitMtx);
            QuitFlag = true;
            pthread_mutex_unlock(&quitMtx);

            pthread_rwlock_unlock(&sharedMtx);
            return NULL;
        }

        ++sharedData;
        printf("[%d] Writer writting [%d]\n", writerId, sharedData);
        pthread_rwlock_unlock(&sharedMtx);
        usleep(100000);
    }
    
}

int main() {
    pthread_t readers[NUM_READERS], writers[NUM_WRITERS];

    // Initialize the shared reader-writer lock
    pthread_rwlock_init(&sharedMtx, NULL);

    // Create reader threads
    for (int i = 0; i < NUM_READERS; i++) {
        int *id = (int*)malloc(sizeof(int));
        *id = i + 1;
        pthread_create(&readers[i], NULL, reader, id);
    }

    // Create writer threads
    for (int i = 0; i < NUM_WRITERS; i++) {
        int *id = (int*)malloc(sizeof(int));
        *id = i + 1;
        pthread_create(&writers[i], NULL, writer, id);
    }

    // Join reader threads
    for (int i = 0; i < NUM_READERS; i++) {
        pthread_join(readers[i], NULL);
    }

    // Join writer threads
    for (int i = 0; i < NUM_WRITERS; i++) {
        pthread_join(writers[i], NULL);
    }

    // Cleanup
    pthread_rwlock_destroy(&sharedMtx);
    printf("All threads completed. Final shared data = %d\n", sharedData);

    return 0;
}