#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <stdbool.h>
#include <unistd.h>

pthread_mutex_t mtx = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cvOdd = PTHREAD_COND_INITIALIZER;
pthread_cond_t cvEven = PTHREAD_COND_INITIALIZER;

int count = 1;

void* printOdd(void *args){
    while(true){
        pthread_mutex_lock(&mtx);

        while(count % 2 == 0 && count <= 100){
            pthread_cond_wait(&cvOdd, &mtx);
        }

        if(count > 100){
            pthread_cond_signal(&cvEven);
            pthread_mutex_unlock(&mtx);
            return NULL;
        }

        printf("Odd ==> %d\n", count);

        ++count;

        pthread_cond_signal(&cvEven);
        pthread_mutex_unlock(&mtx);

        usleep(100000);
    }

    return NULL;
}

void* printEven(void *args){
    while(true){
        pthread_mutex_lock(&mtx);

        while(count % 2 != 0 && count <= 100){
            pthread_cond_wait(&cvEven, &mtx);
        }

        if(count > 100){
            pthread_cond_signal(&cvOdd);
            pthread_mutex_unlock(&mtx);
            return NULL;
        }

        printf("Even ==> %d\n", count);
        ++count;
        
        pthread_cond_signal(&cvOdd);
        pthread_mutex_unlock(&mtx);

        usleep(100000);
    }

    return NULL;
}

int main(){
    pthread_t oddThread;
    pthread_t evenThread;

    int result = pthread_create(&oddThread, NULL, printOdd, NULL);
    if(result != 0){
        perror("Failed to create odd thread with error!\n");
        return 1;
    }

    result = pthread_create(&evenThread, NULL, printEven, NULL);
    if(result != 0){
        perror("Failed to create even thread with error!\n");
        return 2;
    }

    int join_status = pthread_join(oddThread, NULL);
    if(join_status == 0){
        printf("Odd thread joined successfully\n");
    }
    else{
        printf("Failed to join odd thread. Status [%d]\n", join_status);
    }

    join_status = pthread_join(evenThread, NULL);
    if(join_status == 0){
        printf("Even thread joined successfully\n");
    }
    else{
        printf("Failed to join Even thread. Status [%d]\n", join_status);
    }

    return 0;
}