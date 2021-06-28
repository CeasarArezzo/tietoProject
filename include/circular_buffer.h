#ifndef CIRCULAR_BUFFER_H
#define CIRCULAR_BUFFER_H
#include <stdbool.h>
#include <stddef.h>

typedef struct circular_buf circular_buf;

circular_buf* circular_buf_init(size_t);
void circular_buf_free(circular_buf*);
size_t circular_buf_insert(circular_buf*, char*);
char* circular_buf_pop(circular_buf*);
bool circular_buf_empty(circular_buf*);
bool circular_buf_full(circular_buf*);
size_t circular_buf_capacity(circular_buf*, size_t*);
size_t circular_buf_size(circular_buf*, size_t*);

#endif
