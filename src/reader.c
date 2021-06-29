#include <reader.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <circular_buffer.h>
#include <lifetime_struct.h>

static const size_t MAX_LEN = 256;

void *reader_func(void* param)
{
    lifetime_struct* lifetime = param;

    while(lifetime->running)
    {
        //read data from file and send it to analyzer
        FILE *fp = fopen("/proc/stat", "r");
        char* to_send = getFileByLine(fp);
        
        pthread_mutex_lock(&lifetime->analyzer_mutex);
        circular_buf_insert(lifetime->analyzer_buffer, to_send);
        pthread_mutex_unlock(&lifetime->analyzer_mutex);
        sem_post(&lifetime->analyzer_semaphore);
        fclose(fp);
        sleep(1);
    }
    sem_post(&lifetime->analyzer_semaphore);
    // puts("reader done");
    return 0;
}

char* getFileByLine(FILE * fp)
{
    char* to_return = calloc(sizeof(char), 1);
    char* buffer = calloc(sizeof(char), MAX_LEN);
    size_t curr_size = 0;
    while (fgets(buffer, MAX_LEN - 1, fp))
    {
        curr_size += strlen(buffer);
        to_return = realloc(to_return, curr_size+1);
        strcat(to_return, buffer);
    }
    free(buffer);
    return to_return;
}
