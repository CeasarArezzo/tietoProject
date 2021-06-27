#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <reader.h>
#include <string.h>
#include <circular_buffer.h>
#include <lifetime_struct.h>

void test_circular_buffer();
void run_threads();

int main(int argc, char **argv) 
{
    if (argc > 1)
    {
        if (strcmp(argv[1], "-t") == 0)
        {
            puts("test mode");
            test_circular_buffer();
            return EXIT_SUCCESS;
        }
    }
    run_threads();
    // cbuf_handle myBuf = circular_buf_init(5);
    // circular_buf_pop(myBuf);
    // // char* tmp = malloc(sizeof(char) * 10);
    // char* tmp = "kanapka";
    // circular_buf_insert(myBuf, tmp);
    // printf("%s\n", circular_buf_pop(myBuf));
    // tmp = "kanapka2";
    // circular_buf_insert(myBuf, tmp);
    // tmp = NULL;
    // char* res = 0;
    // printf("%s\n", circular_buf_pop(myBuf));

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

void run_threads()
{
    lifetime_struct* lifetime = init_lifetime_struct();
    pthread_t reader_thread;
    pthread_create(&reader_thread, NULL, &analyzer_func, lifetime);
    
    pthread_join(reader_thread, NULL);
    lifetime_struct_free(lifetime);
}

void test_circular_buffer()
{
    puts("testing circular buffer");
    cbuf_handle cbuf = circular_buf_init(5);
    char* tmp[] = {"s0", "s1", "s2", "s3", "s4", "s5"};
    char* res = circular_buf_pop(cbuf);
    if(res == NULL)
    {
        puts("poping from empty - passed");
    }
    char* read_data;
    circular_buf_insert(cbuf, tmp[0]);
    if( strcmp(tmp[0], read_data = circular_buf_pop(cbuf)) == 0)
    {
        circular_buf_insert(cbuf, tmp[1]);
        circular_buf_insert(cbuf, tmp[2]);
        circular_buf_insert(cbuf, tmp[3]);
        bool result = true;
        for (size_t i = 1; i< 4; i++)
        {
            if(strcmp(tmp[i], read_data = circular_buf_pop(cbuf)) != 0)
            {
                result = false;
            }
        }
        if (result)
        {
            puts("insert many elements - passed");
        }
    }
    circular_buf_insert(cbuf, tmp[0]);
    circular_buf_free(cbuf);
}
