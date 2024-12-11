#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <errno.h>
#include <pthread.h>
#include <semaphore.h>
#include <time.h>

#ifndef CLOCK_REALTIME
#define CLOCK_REALTIME 0
#endif

int number = 0;

static pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

static sem_t semaphore;

static void* do_stuff(void* arg)
{
    printf("doing stuff...\n");

    //retrieveing the argument
    // int num = *(int*)arg;
    // free(arg);
    // printf("received number %d\n", num);

    return(0);
}

static void* increment_number(void* arg)
{
    for(int i = 0; i < 10000000; i++)
    {
        //mutexes are needed for shared global variables
        // pthread_mutex_lock(&mutex);
        number += 1;
        // pthread_mutex_unlock(&mutex);
    }
    return 0;
}

static void* wait_on_semaphore(void* arg)
{
    //waiting on a semaphore with a timeout
    // struct timespec ts;
    // clock_gettime(CLOCK_REALTIME, &ts);
    // ts.tv_sec += 6;
    // int result = sem_timedwait(&semaphore, &ts);
    // if(result == -1 && errno == ETIMEDOUT)
    // {
    //     printf("timed out!\n");
    // }
    // else
    // {
    //     printf("done waiting!\n");
    // }

    //waiting on a semaphore
    sem_wait(&semaphore);
    printf("done waiting!\n");
    return 0;
}

int main(int argc, char * argv[])
{
    pthread_t thread;
    // pthread_t thread2;
    
    //creating a thread
    // pthread_create(&thread, NULL, do_stuff, NULL);

    //creating a thread and passing an argument
    // int * num = malloc(sizeof(int));
    // *num = 4;
    // pthread_create(&thread, NULL, do_stuff, num);

    //two threads working on the same global variable
    // pthread_create(&thread, NULL, increment_number, NULL);
    // pthread_create(&thread2, NULL, increment_number, NULL);

    //creating a semaphore and making the thread wait for it
    // sem_init(&semaphore, 0, 0);
    // pthread_create(&thread, NULL, wait_on_semaphore, NULL);

    // sleep(5);
    // sem_post(&semaphore);

    //make sure you wait for threads to finish before terminating
    // pthread_join(thread, NULL);
    // pthread_join(thread2, NULL);
    // printf("number: %d\n", number);
}
