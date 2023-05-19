#include <pthread.h>


#define ARRAY_SIZE 10
#define WORKERS_COUNT 3
#define PAUSE_LENGTH 1
#ifndef PROTECTION
#define PROTECTION 1 // 1 - using semaphores/mutexes, 0 - does not
#endif

static struct thread_start_data {
    unsigned int randseed;
    int *array;
#if PROTECTION == 1
    pthread_mutex_t *arr_mutex;
    sem_t *data_sem;
#endif
};