#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include <reader.h>
#include <circular_buffer.h>

#define DEFAULT_LEN 256

char* getFileByLine(FILE * fp)
{
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

char* getFileByChar(FILE * fp)
{
    return NULL;
}

int main() 
{
    pthread_t readerThread;
    pthread_create(&readerThread, NULL, &readerFunc, NULL);
    FILE *fp = fopen("/proc/stat", "rb");
    
    if (fp != NULL)
    {
        char * buffer = getFileByLine(fp);
        fputs(buffer, stdout);
        free(buffer);
        fclose(fp);
    }
    // int foo = 5;
    // char bar[foo];
    pthread_join(readerThread, NULL);
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
