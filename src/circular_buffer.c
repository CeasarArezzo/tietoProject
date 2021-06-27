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

static void insert_move(cbuf_handle cbuf);
static void pop_move(cbuf_handle cbuf);

cbuf_handle circular_buf_init(size_t size)
{
    if (size)
    {
        cbuf_handle cbuf = malloc(sizeof(circular_buf));
        if (cbuf)
        {
            cbuf->buffer = calloc(size, sizeof(char*));
            cbuf->head = 0;
            cbuf->tail = 0;
            cbuf->full = false;
	        cbuf->capacity = size;
            // if (pthread_mutex_init(&cbuf->lock, NULL))
            // {
            //     return NULL;
            // }
            // puts("mutex initialized");
            // if(sem_init(&cbuf->empty, 0, SEM_INIT_VALUE))
            // {
            //     return NULL;
            // }
            // puts("semaphore initialized");
            return cbuf;
        }
    }
    return NULL;
}

void circular_buf_free(cbuf_handle cbuf)
{
    if (cbuf)
    {
        //delete all data?
        free(cbuf->buffer);
        free(cbuf);
    }
}

size_t circular_buf_insert(cbuf_handle cbuf, char* data)
{
    if (cbuf)
    {
        cbuf->buffer[cbuf->head] = data;
        // printf("%s\n", cbuf->buffer[cbuf->head]);
        insert_move(cbuf);
        return 0;
    }
    return 1;
}

char* circular_buf_pop(cbuf_handle cbuf)
{
    if (cbuf)
    {
        if (!circular_buf_empty(cbuf))
        {
            char* tmp = cbuf->buffer[cbuf->tail];
            pop_move(cbuf);
            // printf("%s\n", tmp);
            return tmp;
        }
    }
    return NULL;
}

bool circular_buf_empty(cbuf_handle cbuf)
{
    if (cbuf)
    {
        return (!circular_buf_full(cbuf) && (cbuf->head == cbuf->tail));
    }
    return NULL;
}

bool circular_buf_full(cbuf_handle cbuf)
{
    if (cbuf)
    {
        return cbuf->full;
    }
    return NULL;
}

size_t circular_buf_capacity(cbuf_handle cbuf, size_t* res)
{
    if (cbuf)
    {
        *res = cbuf->capacity;
        return 0;
    }
    return 1;
}

size_t circular_buf_size(cbuf_handle cbuf, size_t* res)
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

static void insert_move(cbuf_handle cbuf)
{
	assert(cbuf);

    cbuf->head = (cbuf->head + 1) % cbuf->capacity;
    if(circular_buf_full(cbuf))
    {
        cbuf->tail = (cbuf->tail + 1) % cbuf->capacity;
    }
    cbuf->full = (cbuf->head == cbuf->tail);
}

static void pop_move(cbuf_handle cbuf)
{
	assert(cbuf);
    cbuf->full = false;
	cbuf->tail = (cbuf->tail + 1) % cbuf->capacity;
}