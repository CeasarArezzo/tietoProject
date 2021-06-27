#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include <circular_buffer.h>
#include <lifetime_struct.h>
#include <reader.h>
#include <analyzer.h>

void run_tests();
void test_circular_buffer();
void run_threads();

int main(int argc, char **argv) 
{
    if (argc > 1)
    {
        if (strcmp(argv[1], "-t") == 0)
        {
            run_tests();
            return EXIT_SUCCESS;
        }
    }
    run_threads();

    return EXIT_SUCCESS;
}

void run_threads()
{
    lifetime_struct* lifetime = init_lifetime_struct();
    pthread_t reader_thread;
    pthread_t analyzer_thread;
    pthread_create(&reader_thread, NULL, &reader_func, lifetime);
    pthread_create(&analyzer_thread, NULL, &analyzer_func, lifetime);
    
    pthread_join(reader_thread, NULL);
    pthread_join(analyzer_thread, NULL);
    lifetime_struct_free(lifetime);
    puts("job done");
}

void run_tests()
{
    puts("test mode");
    test_circular_buffer();
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
