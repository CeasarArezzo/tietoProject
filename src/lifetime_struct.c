#include <stdlib.h>
#include <lifetime_struct.h>
#include <consts.h>

lifetime_struct* init_lifetime_struct()
{
    lifetime_struct* ltime = malloc(sizeof(lifetime_struct));
    if (ltime)
    {
        ltime->running = true;
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
