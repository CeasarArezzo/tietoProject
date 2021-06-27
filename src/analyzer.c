#include <analyzer.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <circular_buffer.h>
#include <lifetime_struct.h>

#define USED_COLS_AMOUNT 8

size_t** last_read_data;
size_t* prev_idle;
size_t* prev_total;
size_t* curr_idle;
size_t* curr_total;
size_t cpu_amount;

void* analyzer_func(void* param)
{
    lifetime_struct* lifetime = param;
    char* first_read = pop_once(lifetime);
    cpu_amount = count_cores(first_read);
    first_process(first_read);

    // for (size_t i = 0; i < 5; i++)
    while(lifetime->running)
    {
        char* received = pop_once(lifetime);
        char* to_send = process_data(received);
        fputs(received, stdout);
        free(received);
    }
    return 0;
}

char* process_data(char* curr_read)
{
    char* to_return = "\0";

    curr_read = strstr(curr_read, "cpu0");
    for (size_t i = 0; i < cpu_amount; i++)
    {
        size_t* new_data = calloc(sizeof(size_t), USED_COLS_AMOUNT);

        sscanf(curr_read, "cpu %zu %zu %zu %zu %zu %zu %zu %zu ", &new_data[0], &new_data[1], &new_data[2],
            &new_data[3], &new_data[4], &new_data[5], &new_data[6], &new_data[7]);   
        curr_read = strstr(curr_read+1, "cpu");

        size_t idle = new_data[3] + new_data[4];

        free(new_data);
    }

    return to_return;
}

void first_process(char* curr_read)
{
    // last_read_data = malloc(sizeof(size_t*) * cpu_amount);
    prev_idle = malloc(sizeof(size_t*) * cpu_amount);
    prev_total = malloc(sizeof(size_t*) * cpu_amount);
    curr_idle = malloc(sizeof(size_t*) * cpu_amount);
    curr_total = malloc(sizeof(size_t*) * cpu_amount);
    // for (size_t i = 0; i < cpu_amount; i++)
    // {
    //     last_read_data[i] = malloc(sizeof(size_t) * USED_COLS_AMOUNT);
    // }

    puts(curr_read);
    curr_read = strstr(curr_read, "cpu0");
    for (size_t i = 0; i < cpu_amount; i++)
    {
        size_t* new_data = calloc(sizeof(size_t), USED_COLS_AMOUNT);

        size_t unused;
        sscanf(curr_read, "cpu%zu %zu %zu %zu %zu %zu %zu %zu %zu ", &unused, &new_data[0], &new_data[1], &new_data[2],
            &new_data[3], &new_data[4], &new_data[5], &new_data[6], &new_data[7]);    
        curr_read = strstr(curr_read+1, "cpu");

        prev_total[i] = 0;
        // printf("cpu%zu ", i);
        for (size_t j = 0; j < USED_COLS_AMOUNT; j++)
        {
            // printf("%zu ", new_data[j]);
            prev_total[i] += new_data[j];
        }
        // printf("\n");
        prev_idle[i] = new_data[3] + new_data[4];
    }
    for (size_t i = 0; i < cpu_amount; i++)
    {
        printf("cpu%lu, total %lu, idle %lu\n", i, prev_total[i], prev_idle[i]);
    }
}

char* pop_once(lifetime_struct* ltime)
{
    sem_wait(&ltime->analyzer_semaphore);
    pthread_mutex_lock(&ltime->analyzer_mutex);
    char* received = circular_buf_pop(ltime->analyzer_buffer);
    pthread_mutex_unlock(&ltime->analyzer_mutex);

    return received;
}

size_t count_cores(char* first_read)
{
    char* new = first_read+1;
    size_t curr_count = 0;
    while(new != NULL)
    {
        new++;
        new = strstr(new, "cpu");
        if (new != NULL)
        {
            curr_count++;
        }
    }
    
    return curr_count;
}
