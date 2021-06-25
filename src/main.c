#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include <reader.h>
#include <circular_buffer.h>

#define DEFAULT_LEN 256

char* getFileByLine(FILE * fp)
{
    cbuf_handle_t tmp = circular_buf_init(10);
    char chunk[DEFAULT_LEN];
    size_t len = sizeof(chunk);
    char *line = malloc(len);
    char *toReturn = malloc(0);
    size_t currSize = 0;
    if (line != NULL && toReturn != NULL)
    {
        line[0] = '\0';
        while(fgets(chunk, sizeof(chunk), fp) != NULL) 
        {
            size_t len_used = strlen(line);
            size_t chunk_used = strlen(chunk);

            if(len - len_used < chunk_used) 
            {
                len *= 2;
                if ((line = realloc(line, len)) == NULL)
                {
                    perror("Unable to reallocate memory for the line buffer.");
                    free(line);
                    exit(1);
                }
            }

            strncpy(line + len_used, chunk, len - len_used);
            len_used += chunk_used;

            if(line[len_used - 1] == '\n') 
            {
                currSize += len_used;
                // printf("realloc %lu\n", currSize);
                toReturn = realloc(toReturn, currSize);
                strcat(toReturn, line);
                // fputs(line, stdout);
                // fputs("|*\n", stdout);
                line[0] = '\0';
            }
        }
        // fputs(toReturn, stdout);
    }
    free(line);
    return toReturn;
}

void test_circular_buffer();

int main() 
{
    test_circular_buffer();
    return EXIT_SUCCESS;
    cbuf_handle_t myBuf = circular_buf_init(5);
    // char* tmp = malloc(sizeof(char) * 10);
    char* tmp = "kanapka";
    circular_buf_insert(myBuf, tmp);
    tmp = NULL;
    char* res = 0;
    puts("here");
    printf("%s\n", circular_buf_pop(myBuf));
    puts("here");
    return 0;
    pthread_t reader_thread;
    pthread_create(&reader_thread, NULL, &readerFunc, NULL);
    FILE *fp = fopen("/proc/stat", "rb");
    
    if (fp != NULL)
    {
        char * buffer = getFileByLine(fp);
        fputs(buffer, stdout);
        free(buffer);
        fclose(fp);
    }
    pthread_join(reader_thread, NULL);

    // fp = fopen("/proc/stat", "rb");
    // buffer = getFileByChar(fp);
    // fputs(buffer, stdout);

    // char last;
    // last = '0';
    // for (size_t i = 0; i < 5000; i++)
    // {
    //     char * buffer = getFileByLine(fp);
    //     fseek(fp, 0, SEEK_SET);
    //     // printf("%c\n", buffer[8]);
    //     if (buffer[8] != last && i != 0)
    //     {
    //         printf("zmiana %c -> %c na %lu\n", last, buffer[8], i);
    //     }
    //     last = buffer[8];
    //     // fputs(buffer, stdout);
    //     free(buffer);
    //     // fputs(buffer[10], stdout);
    // }
    // char * buffer = getFileByLine(fp);
    // fputs(buffer, stdout);
    // char chunk[128];
    // size_t length = sizeof(chunk);
    // buffer = malloc(length);

    // if(fp && buffer)
    // {
    //     buffer[0] = '\0';
    //     while(fgets(chunk, sizeof(chunk), fp) != NULL) 
    //         {
    //             fputs(chunk, stdout);
    //             fputs("|*\n", stdout);  // marker string used to show where the content of the chunk array has ended
    //         }
    //     fclose(fp);
    // }

    return EXIT_SUCCESS;
}

void test_circular_buffer()
{
    puts("testing circular buffer");
    cbuf_handle_t cbuf = circular_buf_init(5);
    char* tmp[] = {"s0", "s1", "s2", "s3", "s4", "s5"};
    char* res = circular_buf_pop(cbuf);
    if(res == NULL)
    {
        puts("poping from empty - passed");
    }
    circular_buf_insert(cbuf, tmp[0]);
    puts(circular_buf_pop(cbuf));
}
