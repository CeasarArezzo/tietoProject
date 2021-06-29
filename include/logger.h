#ifndef LOGGER_H
#define LOGGER_H
#include <lifetime_struct.h>

void* logger_func(void*);
void send_to_logger(char*, lifetime_struct*);

#endif
