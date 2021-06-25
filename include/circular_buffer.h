#ifndef CIRCULAR_BUFFER_H
#define CIRCULAR_BUFFER_H
#include <stdio.h>
#include <stdbool.h>

typedef struct circular_buf_t circular_buf_t;
typedef circular_buf_t* cbuf_handle_t;

cbuf_handle_t circular_buf_init(size_t);
void circular_buf_free(cbuf_handle_t);
size_t circular_buf_insert(cbuf_handle_t, char*);
char* circular_buf_pop(cbuf_handle_t, char**);
bool circular_buf_empty(cbuf_handle_t);
bool circular_buf_full(cbuf_handle_t);
size_t circular_buf_capacity(cbuf_handle_t, size_t*);
size_t circular_buf_size(cbuf_handle_t, size_t*);

#endif