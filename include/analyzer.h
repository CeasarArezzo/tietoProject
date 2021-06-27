#ifndef ANALYZER_H
#define ANALYZER_H
#include <lifetime_struct.h>

void* analyzer_func(void*);
char* pop_once(lifetime_struct*);
size_t count_cores(char*);
void first_process(char*);
char* process_data(char*);

#endif
