#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>
#include <unistd.h>>
#include <pthread.h>
#include <stdbool.h>

sem_t semOdd;
sem_t semEven;
int count = 1;

void* printOdd(void *args){
    while(true){
        sem_wait(&semOdd);

        if(count > 100){
            sem_post(&semEven);
            break;
        }

        printf("Odd => %d\n", count);
        ++count;
        sem_post(&semEven);

        usleep(100000);
    }

    return NULL;
}

void* printEven(void *args){
    while(true){
        sem_wait(&semEven);

        if(count > 100){
            sem_post(&semOdd);
            break;
        }

        printf("Even => %d\n", count);
        ++count;
        sem_post(&semOdd);

        usleep(100000);
    }

    return NULL;
}


int main(){
    sem_init(&semOdd, 0, 1);
    sem_init(&semEven, 0, 0);

    pthread_t threadOdd, threadEven;

    int result = pthread_create(&threadOdd, NULL, printOdd, NULL);
    if(result != 0){
        perror("Failed to create odd thread!\n");
        return 1;
    }

    result = pthread_create(&threadEven, NULL, printEven, NULL);
    if(result != 0){
        perror("Failed to create even thread!\n");
        return 1;
    }

    int joinStatus = pthread_join(threadOdd, NULL);
    joinStatus = pthread_join(threadEven, NULL);

    sem_destroy(&semOdd);
    sem_destroy(&semEven);
    return 0;
}