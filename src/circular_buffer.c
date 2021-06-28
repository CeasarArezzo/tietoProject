#include <circular_buffer.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>


struct circular_buf {
	char** buffer;
	size_t head;
	size_t tail;
	size_t capacity;
    bool full;
};

static void insert_move(circular_buf* cbuf);
static void pop_move(circular_buf* cbuf);

circular_buf* circular_buf_init(size_t size)
{
    if (size)
    {
        circular_buf* cbuf = malloc(sizeof(circular_buf));
        if (cbuf)
        {
            cbuf->buffer = calloc(size, sizeof(char*));
            cbuf->head = 0;
            cbuf->tail = 0;
            cbuf->full = false;
	        cbuf->capacity = size;
            return cbuf;
        }
    }
    return NULL;
}

void circular_buf_free(circular_buf* cbuf)
{
    if (cbuf)
    {
        while(!circular_buf_empty(cbuf))
        {
            free(circular_buf_pop(cbuf));
        }
        free(cbuf->buffer);
        free(cbuf);
    }
}

size_t circular_buf_insert(circular_buf* cbuf, char* data)
{
    if (cbuf)
    {
        cbuf->buffer[cbuf->head] = data;
        insert_move(cbuf);
        return 0;
    }
    return 1;
}

char* circular_buf_pop(circular_buf* cbuf)
{
    if (cbuf)
    {
        if (!circular_buf_empty(cbuf))
        {
            char* tmp = cbuf->buffer[cbuf->tail];
            pop_move(cbuf);
            return tmp;
        }
    }
    return NULL;
}

bool circular_buf_empty(circular_buf* cbuf)
{
    if (cbuf)
    {
        return (!circular_buf_full(cbuf) && (cbuf->head == cbuf->tail));
    }
    return NULL;
}

bool circular_buf_full(circular_buf* cbuf)
{
    if (cbuf)
    {
        return cbuf->full;
    }
    return NULL;
}

size_t circular_buf_capacity(circular_buf* cbuf, size_t* res)
{
    if (cbuf)
    {
        *res = cbuf->capacity;
        return 0;
    }
    return 1;
}

size_t circular_buf_size(circular_buf* cbuf, size_t* res)
{
    if (cbuf)
    {
        size_t size = cbuf->capacity;
        if(!circular_buf_full(cbuf))
        {
            if(cbuf->head >= cbuf->tail)
            {
                size = cbuf->head - cbuf->tail;
            }
            else
            {
                size = cbuf->capacity + cbuf->head - cbuf->tail;
            }
        }
        *res = size;
        return 0;
    }
    return 1;
}

static void insert_move(circular_buf* cbuf)
{
	assert(cbuf);

    cbuf->head = (cbuf->head + 1) % cbuf->capacity;
    if(circular_buf_full(cbuf))
    {
        cbuf->tail = (cbuf->tail + 1) % cbuf->capacity;
    }
    cbuf->full = (cbuf->head == cbuf->tail);
}

static void pop_move(circular_buf* cbuf)
{
	assert(cbuf);
    cbuf->full = false;
	cbuf->tail = (cbuf->tail + 1) % cbuf->capacity;
}