#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define MAX_LEN 256

char* getFileByLine(FILE * fp)
{
    char chunk[128];
    size_t len = sizeof(chunk);
    char *line = malloc(len);
    if (line != NULL)
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
                fputs(line, stdout);
                // fputs("|*\n", stdout);
                line[0] = '\0';
            }
        }
    }
    return 0;
}

char* getFileByChar(FILE * fp)
{
    
}

int main(int argc, char* argv[argc+1]) 
{
    // struct stat st;
    // stat("/proc/stat", &st);
    // int size = st.st_size;
    FILE *fp = fopen("/proc/stat", "rb");
    
    char * buffer = getFileByLine(fp);
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
    fclose(fp);

    return EXIT_SUCCESS;
}