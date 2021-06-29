#include <logger.h>
#include <stdio.h>
#include <lifetime_struct.h>
#include <string.h>
#include <stdlib.h>

#define LOGGER_FILENAME "logger.txt"
#define WRITE_MODE "w+"
#define MAX_LOG_SIZE 256

static char* pop_once(lifetime_struct*);

void* logger_func(void* param)
{
    lifetime_struct* lifetime = param;
    FILE *fp = fopen(LOGGER_FILENAME, WRITE_MODE);
    while(lifetime->running)
    {
        char* read_message = pop_once(lifetime);
        fputs(read_message, fp);
        // puts(read_message);
        free(read_message);
        fflush(fp);
    }
    pthread_mutex_lock(&lifetime->logger_mutex);
    while(!circular_buf_empty(lifetime->logger_buffer))
    {
        char* read_message = circular_buf_pop(lifetime->logger_buffer);
        fputs(read_message, fp);
        // puts(read_message);
        free(read_message);
        fflush(fp);
    }
    pthread_mutex_unlock(&lifetime->logger_mutex);
    fclose(fp);
    return 0;
}

void send_to_logger(char* tag, char* to_log, lifetime_struct* ltime)
{
    if (tag == NULL || to_log == NULL || ltime == NULL)
    {
        return;
    }
    //callocing +1 to keep space for \0 symbol
    char* to_send = calloc(sizeof(char), strlen(tag) + strlen(to_log) + strlen(":\t") + strlen("\n") + 1);
    to_send[0] = '\0';
    to_send = strcat(to_send, tag);
    to_send = strcat(to_send, ":\t");
    to_send = strcat(to_send, to_log);
    to_send = strcat(to_send, "\n");
    pthread_mutex_lock(&ltime->logger_mutex);
    circular_buf_insert(ltime->logger_buffer, to_send);
    pthread_mutex_unlock(&ltime->logger_mutex);
    sem_post(&ltime->logger_semaphore);
}

static char* pop_once(lifetime_struct* ltime)
{
    if (ltime)
    {
        sem_wait(&ltime->logger_semaphore);
        pthread_mutex_lock(&ltime->logger_mutex);
        char* received = circular_buf_pop(ltime->logger_buffer);
        pthread_mutex_unlock(&ltime->logger_mutex);

        return received;
    }
    return NULL;
}
