// main function for thread example:
void* my_thread_main(void *arg) {

}

//thread creation
// pthread_t - type for thread id
int pthread_create(pthread_t* thr, pthread_attr_t* attr, void*(*start_routing)(void*), void* arg);


// thread close (thread finish)
void pthread_exit(void *retval);
// or just return

// thread wait until another thread will finish
int pthread_join(pthread_t th, void** result);


// detached mode for thread
int pthread_detach(pthread_t th);

// self id
pthread_t pthread_self();
// pthread_detach(pthread_self())

// thread can finish another thread before finish
int pthread_cancel(pthread_t th);
