#ifndef ANALYZER_H
#define ANALYZER_H
#include <lifetime_struct.h>

void* analyzer_func(void*);
char* pop_once_analyzer(lifetime_struct*);
size_t count_cores(char*);
void first_process(char*);
char* process_data(char*);
void calculate_usage(char*, size_t*, size_t*);
void free_data();

#endif
