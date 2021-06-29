#ifndef LIFETIME_STRUCT_H
#define LIFETIME_STRUCT_H
#include <circular_buffer.h>
#include <pthread.h>
#include <semaphore.h>
#include <stdbool.h>

typedef struct lifetime_struct{
    pthread_mutex_t          analyzer_mutex;
    pthread_mutex_t          printer_mutex;
    pthread_mutex_t          logger_mutex;
    sem_t                    analyzer_semaphore;
    sem_t                    printer_semaphore;
    sem_t                    logger_semaphore;
	circular_buf*            analyzer_buffer;
	circular_buf*            printer_buffer;
	circular_buf*            logger_buffer;
    volatile _Atomic(bool)   running;

} lifetime_struct;

lifetime_struct* init_lifetime_struct(void);
void lifetime_struct_free(lifetime_struct*);

#endif
