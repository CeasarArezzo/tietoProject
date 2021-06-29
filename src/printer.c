#include <stdlib.h>
#include <stdio.h>
#include <lifetime_struct.h>
#include <printer.h>
#include <logger.h>

static char* pop_once(lifetime_struct*);

#define log_tag "PRINTER"
#define msg_start "starting work"
#define msg_printing "got data to print"
#define msg_end "ending work"

void* printer_func(void* param)
{
    lifetime_struct* lifetime = param;
    send_to_logger(log_tag, msg_start, lifetime);
    while(lifetime->running)
    {
        char* read_data = pop_once(lifetime);
        if (read_data)
        {
            send_to_logger(log_tag, msg_printing, lifetime);
            puts(read_data);
            free(read_data);
        }
    }
    send_to_logger(log_tag, msg_end, lifetime);
    sem_post(&lifetime->logger_semaphore);
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
