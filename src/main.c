#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include <signal.h>
#include <circular_buffer.h>
#include <lifetime_struct.h>
#include <reader.h>
#include <analyzer.h>
#include <printer.h>

void run_tests();
void test_circular_buffer();
void run_threads();
void term(int);

lifetime_struct* lifetime;

int main(int argc, char **argv) 
{
    signal(SIGTERM, term);

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

void term(int signum)
{
    if (lifetime)
    {
        lifetime->running = false;
    }
}

void run_threads()
{
    lifetime = init_lifetime_struct();
    pthread_t reader_thread;
    pthread_t analyzer_thread;
    pthread_t printer_thread;
    pthread_create(&reader_thread, NULL, &reader_func, lifetime);
    pthread_create(&analyzer_thread, NULL, &analyzer_func, lifetime);
    pthread_create(&printer_thread, NULL, &printer_func, lifetime);
    
    pthread_join(reader_thread, NULL);
    pthread_join(analyzer_thread, NULL);
    pthread_join(printer_thread, NULL);
    lifetime_struct_free(lifetime);
}

void run_tests()
{
    puts("test mode");
    test_circular_buffer();
}

void test_circular_buffer()
{
    puts("testing circular buffer");
    circular_buf* cbuf = circular_buf_init(5);
    char* tmp = calloc(sizeof(char*), 6);
    for (size_t i = 0; i < 6; i++)
    {
        tmp[i] = 's';
    }
    char* res = circular_buf_pop(cbuf);
    if(res == NULL)
    {
        puts("poping from empty - passed");
    }
    char* read_data;
    circular_buf_insert(cbuf, &tmp[0]);
    if( strcmp(tmp, read_data = circular_buf_pop(cbuf)) == 0)
    {
        circular_buf_insert(cbuf, tmp);
        circular_buf_insert(cbuf, tmp);
        circular_buf_insert(cbuf, tmp);
        bool result = true;
        for (size_t i = 1; i< 4; i++)
        {
            if(strcmp(tmp, read_data = circular_buf_pop(cbuf)) != 0)
            {
                result = false;
            }
        }
        if (result)
        {
            puts("insert many elements - passed");
        }
        circular_buf_pop(cbuf);
        circular_buf_pop(cbuf);
    }
    circular_buf_insert(cbuf, tmp);
    char* new_ins = malloc(sizeof(char) * 1);
    new_ins[0] = 'a';
    circular_buf_insert(cbuf, new_ins);
    circular_buf_free(cbuf);
}
