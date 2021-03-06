#include <reader.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <circular_buffer.h>
#include <lifetime_struct.h>
#include <logger.h>

#define FILENAME "/proc/stat"
#define OPEN_MODE "r"
#define MAX_LEN 256
#define WAIT_TIME 1

#define log_tag "READER"
#define msg_start "starting work"
#define msg_read "read data from source file"
#define msg_sent "data sent to analyzer"
#define msg_end "ending work"

static char* getFileByLine(FILE * fp);

void *reader_func(void* param)
{
    lifetime_struct* lifetime = param;
    send_to_logger(log_tag, msg_start, lifetime);

    while(lifetime->running)
    {
        //read data from file and send it to analyzer
        FILE *fp = fopen(FILENAME, OPEN_MODE);
        char* to_send = getFileByLine(fp);
        send_to_logger(log_tag, msg_read, lifetime);
        
        pthread_mutex_lock(&lifetime->analyzer_mutex);
        circular_buf_insert(lifetime->analyzer_buffer, to_send);
        pthread_mutex_unlock(&lifetime->analyzer_mutex);
        sem_post(&lifetime->analyzer_semaphore);
        fclose(fp);
        send_to_logger(log_tag, msg_sent, lifetime);
        sleep(WAIT_TIME);
    }
    send_to_logger(log_tag, msg_end, lifetime);
    sem_post(&lifetime->analyzer_semaphore);
    return 0;
}

static char* getFileByLine(FILE * fp)
{
    char* to_return = calloc(sizeof(char), 1);
    char* buffer = calloc(sizeof(char), MAX_LEN);
    size_t curr_size = 0;
    //-1 so space for \0 is kept
    while (fgets(buffer, MAX_LEN - 1, fp))
    {
        curr_size += strlen(buffer);
        to_return = realloc(to_return, curr_size+1);
        strcat(to_return, buffer);
    }
    free(buffer);
    return to_return;
}
