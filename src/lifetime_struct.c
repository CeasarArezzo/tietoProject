#include <stdlib.h>
#include <lifetime_struct.h>
#include <pthread.h>
#include <semaphore.h>
#include <circular_buffer.h>

#define BUFFER_SIZE 256
#define SEM_INIT_VALUE 0

struct lifetime_struct {
	cbuf_handle analyzer_buffer;
	cbuf_handle printer_buffer;
    pthread_mutex_t analyzer_mutex;
    pthread_mutex_t printer_mutex;
    sem_t analyzer_semaphore;
    sem_t printer_semaphore;
};

lifetime_struct* init_lifetime_struct()
{
    lifetime_struct* ltime = malloc(sizeof(lifetime_struct));
    if (ltime)
    {
        ltime->analyzer_buffer = circular_buf_init(BUFFER_SIZE);
        if (pthread_mutex_init(&ltime->analyzer_mutex, NULL))
        {
            return NULL;
        }
        if(sem_init(&ltime->analyzer_semaphore, 0, SEM_INIT_VALUE))
        {
            return NULL;
        }
        ltime->printer_buffer = circular_buf_init(BUFFER_SIZE);
        if (pthread_mutex_init(&ltime->printer_mutex, NULL))
        {
            return NULL;
        }
        if(sem_init(&ltime->printer_semaphore, 0, SEM_INIT_VALUE))
        {
            return NULL;
        }
        if (ltime->analyzer_buffer && ltime->printer_buffer)
        {
            return ltime;
        }
    }
    return NULL;
}

void lifetime_struct_free(lifetime_struct* ltime)
{
    if (ltime)
    {
        circular_buf_free(ltime->analyzer_buffer);
        circular_buf_free(ltime->printer_buffer);
        pthread_mutex_destroy(&ltime->analyzer_mutex);
        pthread_mutex_destroy(&ltime->printer_mutex);
        sem_destroy(&ltime->analyzer_semaphore);
        sem_destroy(&ltime->printer_semaphore);
        free(ltime);
    }
}

cbuf_handle get_analyzer_buffer(lifetime_struct* ltime)
{
    return ltime->analyzer_buffer;
}

cbuf_handle get_printer_buffer(lifetime_struct* ltime)
{
    return ltime->printer_buffer;
}