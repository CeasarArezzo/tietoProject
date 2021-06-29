#include <stdlib.h>
#include <stdio.h>
#include <lifetime_struct.h>
#include <printer.h>

static char* pop_once(lifetime_struct*);

void* printer_func(void* param)
{
    lifetime_struct* lifetime = param;
    while(lifetime->running)
    {
        char* read_data = pop_once(lifetime);
        if (read_data)
        {
            puts(read_data);
            free(read_data);
        }
    }
    // puts("printer done");
    return 0;
}

static char* pop_once(lifetime_struct* ltime)
{
    sem_wait(&ltime->printer_semaphore);
    pthread_mutex_lock(&ltime->printer_mutex);
    char* received = circular_buf_pop(ltime->printer_buffer);
    pthread_mutex_unlock(&ltime->printer_mutex);

    return received;
}
