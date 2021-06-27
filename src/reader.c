#include <reader.h>
#include <stdio.h>
#include <string.h>
#include <circular_buffer.h>
#include <lifetime_struct.h>
#include <stdlib.h>
#include <unistd.h>

#define MAX_LEN 256
#define DEFAULT_SIZE 256

void *analyzer_func(void* param)
{
    lifetime_struct* lifetime = param;
    cbuf_handle analyzer_buffer = get_analyzer_buffer(lifetime);

    while(1)
    {
        FILE *fp = fopen("/proc/stat", "rb");
        char* to_send = getFileByLine(fp);
        circular_buf_insert(analyzer_buffer, to_send);
        // fputs(to_send, stdout);
        puts("reader sent data to analyzer");
        // free(to_send);
        fclose(fp);
        sleep(1);
    }
    puts("dupa");
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