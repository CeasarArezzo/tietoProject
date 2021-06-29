#include <tests.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <circular_buffer.h>

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
        puts("poping from empty:\t passed");
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
            puts("insert many elements:\t passed");
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
