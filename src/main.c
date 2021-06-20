#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>

#define MAX_LEN 256

int main(int argc, char* argv[argc+1]) 
{
    FILE *fp = fopen("/proc/stat", "r");
    char * buffer = 0;
    size_t length = 0;
    
    assert(fp);
    //read line by line
    fseek64(fp, 0, SEEK_END);
    length = ftell64(fp);
    fseek64(fp, 0, SEEK_SET);
    buffer = malloc(length);
    if (buffer)
    {
        printf("reading\n");
        size_t tmp = fread64(buffer, 1, 30, fp);
        printf("%s\n", buffer);
    }

    // while (fgets(buffer, MAX_LEN - 1, fp))
    // {
    //     // Remove trailing newline
    //     buffer[strcspn(buffer, "\n")] = 0;
    //     printf("%s\n", buffer);
    // }

    fclose(fp);
    return EXIT_SUCCESS;
}