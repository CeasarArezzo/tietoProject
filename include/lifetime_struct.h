#ifndef LIFETIME_STRUCT_H
#define LIFETIME_STRUCT_H
#include <circular_buffer.h>

typedef struct lifetime_struct lifetime_struct;

lifetime_struct* init_lifetime_struct();
void lifetime_struct_free(lifetime_struct*);
cbuf_handle get_analyzer_buffer(lifetime_struct*);
cbuf_handle get_printer_buffer(lifetime_struct*);

#endif
