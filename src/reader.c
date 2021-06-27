#include <reader.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <circular_buffer.h>
#include <lifetime_struct.h>

#define MAX_LEN 256
#define DEFAULT_SIZE 256

void *reader_func(void* param)
{
    lifetime_struct* lifetime = param;

    // for (size_t i = 0; i < 5; i++)
    while(lifetime->running)
    {
        FILE *fp = fopen("/proc/stat", "rb");
        char* to_send = getFileByLine(fp);
        
        pthread_mutex_lock(&lifetime->analyzer_mutex);
        circular_buf_insert(lifetime->analyzer_buffer, to_send);
        pthread_mutex_unlock(&lifetime->analyzer_mutex);
        sem_post(&lifetime->analyzer_semaphore);
        puts("\treader sent data to analyzer");
        fclose(fp);
        sleep(1);
    }
    return 0;
}

char* getFileByLine(FILE * fp)
{
    char* to_return = calloc(1, sizeof(char));
    char buffer[MAX_LEN] = "\0";
    size_t curr_size = 0;
    while (fgets(buffer, MAX_LEN - 1, fp))
    {
        curr_size += strlen(buffer);
        to_return = realloc(to_return, curr_size+1);
        strcat(to_return, buffer);
        // printf("%s", buffer);
    }
    // printf("%s", to_return);
    return to_return;
}