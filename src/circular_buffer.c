#include <circular_buffer.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

struct circular_buf_t {
	char** buffer;
	size_t head;
	size_t tail;
	size_t capacity;
};

static void insert_move(cbuf_handle_t cbuf);
static void pop_move(cbuf_handle_t cbuf);

cbuf_handle_t circular_buf_init(size_t size)
{
    if (size)
    {
        cbuf_handle_t cbuf = malloc(sizeof(circular_buf_t));
        if (cbuf)
        {
            cbuf->buffer = malloc(size * sizeof(char*));
            cbuf->head = 0;
            cbuf->tail = 0;
	        cbuf->capacity = size;
            return cbuf;
        }
    }
    return NULL;
}


void circular_buf_free(cbuf_handle_t cbuf)
{
    if (cbuf)
    {
        //delete all data?
        free(cbuf->buffer);
        free(cbuf);
    }
}

size_t circular_buf_insert(cbuf_handle_t cbuf, char* data)
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

char* circular_buf_pop(cbuf_handle_t cbuf, char** data)
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

bool circular_buf_empty(cbuf_handle_t cbuf)
{
    if (cbuf)
    {
        return (!circular_buf_full(cbuf) && (cbuf->head == cbuf->tail));
    }
    return NULL;
}

bool circular_buf_full(cbuf_handle_t cbuf)
{
    if (cbuf)
    {
        return (cbuf->head == cbuf->tail);
    }
    return NULL;
}

size_t circular_buf_capacity(cbuf_handle_t cbuf, size_t* res)
{
    if (cbuf)
    {
        *res = cbuf->capacity;
        return 0;
    }
    return 1;
}

size_t circular_buf_size(cbuf_handle_t cbuf, size_t* res)
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

static void insert_move(cbuf_handle_t cbuf)
{
	assert(cbuf);

    cbuf->head = (cbuf->head + 1) % cbuf->capacity;
    if(circular_buf_full(cbuf))
    {
        cbuf->tail = (cbuf->tail + 1) % cbuf->capacity;
    }
}

static void pop_move(cbuf_handle_t cbuf)
{
	assert(cbuf);
	cbuf->tail = (cbuf->tail + 1) % cbuf->capacity;
}