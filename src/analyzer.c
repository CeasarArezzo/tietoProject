#include <analyzer.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <circular_buffer.h>
#include <lifetime_struct.h>
#include <consts.h>


size_t* prev_idle;
size_t* prev_total;
size_t* curr_idle;
size_t* curr_total;
size_t cpu_amount;

void* analyzer_func(void* param)
{
    lifetime_struct* lifetime = param;
    char* first_read = pop_once_analyzer(lifetime);
    cpu_amount = count_cores(first_read);
    first_process(first_read);
    free(first_read);

    while(lifetime->running)
    {
        char* received = pop_once_analyzer(lifetime);
        if (received)
        {
            char* to_send = process_data(received);
            free(received);

            pthread_mutex_lock(&lifetime->printer_mutex);
            circular_buf_insert(lifetime->printer_buffer, to_send);
            pthread_mutex_unlock(&lifetime->printer_mutex);
        }
        sem_post(&lifetime->printer_semaphore);
    }
    free_data();
    // puts("analyzer done");
    return 0;
}

void calculate_usage(char* curr_read, size_t* idle, size_t* total)
{
    size_t* new_data = calloc(sizeof(size_t), USED_COLS_AMOUNT);

    size_t unused;
    sscanf(curr_read, "cpu%zu %zu %zu %zu %zu %zu %zu %zu %zu ", &unused, &new_data[0], &new_data[1], &new_data[2],
        &new_data[3], &new_data[4], &new_data[5], &new_data[6], &new_data[7]);     
    
    *total = 0;
    for (size_t j = 0; j < USED_COLS_AMOUNT; j++)
    {
        *total += new_data[j];
    }
    *idle = new_data[3] + new_data[4];
    free(new_data);
}

char* process_data(char* curr_read)
{
    char* to_return = calloc(sizeof(char), strlen(cpu_message) * cpu_amount + 1);

    curr_read = strstr(curr_read, "cpu0");
    for (size_t i = 0; i < cpu_amount; i++)
    {
        prev_idle[i] = curr_idle[i];
        prev_total[i] = curr_total[i];   
        calculate_usage(curr_read, &curr_idle[i], &curr_total[i]);
        curr_read = strstr(curr_read+1, "cpu");

        size_t total_diff = curr_total[i] - prev_total[i];
        size_t idle_diff = curr_idle[i] - prev_idle[i];
        long double usage = (long double)(total_diff - idle_diff) / total_diff;
        char* tmp = calloc(sizeof(char), strlen(cpu_message));
        snprintf(tmp, strlen(cpu_message), cpu_message, i, usage*100);
        to_return = strcat(to_return, tmp);
        free(tmp);
    }
    free(curr_read);

    return to_return;
}

void first_process(char* curr_read)
{
    prev_idle = malloc(sizeof(size_t*) * cpu_amount);
    prev_total = malloc(sizeof(size_t*) * cpu_amount);
    curr_idle = malloc(sizeof(size_t*) * cpu_amount);
    curr_total = malloc(sizeof(size_t*) * cpu_amount);

    curr_read = strstr(curr_read, "cpu0");
    for (size_t i = 0; i < cpu_amount; i++)
    {
        calculate_usage(curr_read, &curr_idle[i], &curr_total[i]);
        curr_read = strstr(curr_read+1, "cpu");
        
    }
}

char* pop_once_analyzer(lifetime_struct* ltime)
{
    sem_wait(&ltime->analyzer_semaphore);
    if (!ltime->running)
    {
        // puts("analyzer done prematurely");
        return NULL;
    }
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

void free_data()
{
    free(prev_idle);
    free(prev_total);
    free(curr_idle);
    free(curr_total);
}
