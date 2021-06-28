#ifndef LIFETIME_STRUCT_H
#define LIFETIME_STRUCT_H
#include <circular_buffer.h>
#include <pthread.h>
#include <semaphore.h>
#include <stdbool.h>

typedef struct lifetime_struct{
	cbuf_handle     analyzer_buffer;
	cbuf_handle     printer_buffer;
    pthread_mutex_t analyzer_mutex;
    pthread_mutex_t printer_mutex;
    sem_t           analyzer_semaphore;
    sem_t           printer_semaphore;
    volatile _Atomic(bool)   running;
} lifetime_struct;

lifetime_struct* init_lifetime_struct();
void lifetime_struct_free(lifetime_struct*);

#endif
