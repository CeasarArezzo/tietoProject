#ifndef CIRCULAR_BUFFER_H
#define CIRCULAR_BUFFER_H
#include <stdbool.h>
#include <stddef.h>

typedef struct circular_buf circular_buf;
typedef circular_buf* cbuf_handle;

cbuf_handle circular_buf_init(size_t);
void circular_buf_free(cbuf_handle);
size_t circular_buf_insert(cbuf_handle, char*);
char* circular_buf_pop(cbuf_handle);
bool circular_buf_empty(cbuf_handle);
bool circular_buf_full(cbuf_handle);
size_t circular_buf_capacity(cbuf_handle, size_t*);
size_t circular_buf_size(cbuf_handle, size_t*);

#endif
