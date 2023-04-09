
// init value for mutex
pthread_mutex_t my_mutex = PTHREAD_MUTEX_INITIALIZER;

//unlock
int pthread_mutex_unlock(pthread_mutex_t *mutex);
//lock (with blocking)
int pthread_mutex_lock(pthread_mutex_t *mutex);
//trylock (without blocking)
int pthread_mutex_trylock(pthread_mutex_t *mutex);

//destroy mutex
int pthread_mutex_destroy(pthread_mutex_t *mutex);


// semaphore init
int sem_init(sem_t *sem, int pshared, unsigned int value);

int sem_post(sem_t *sem); // up
int sem_wait(sem_t *sem); // down
int sem_trywait(sem_t *sem); // non-blocking down

// current value of the semaphore
int sem_getvalue(sem_t *sem, int *sval);

//destroy semaphore
int sem_destroy(sem_t *sem);

