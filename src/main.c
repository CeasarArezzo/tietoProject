#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <signal.h>
#include <circular_buffer.h>
#include <lifetime_struct.h>
#include <reader.h>
#include <analyzer.h>
#include <printer.h>
#include <logger.h>
#include <tests.h>

void run_threads(void);
void term(int);

static lifetime_struct* lifetime;

int main(int argc, char **argv) 
{
    // init_data();
    signal(SIGTERM, term);

    if (argc > 1)
    {
        if (strcmp(argv[1], "-t") == 0)
        {
            run_tests();
            return EXIT_SUCCESS;
        }
    }
    run_threads();

    return EXIT_SUCCESS;
}

void term(int signum)
{
    if (lifetime)
    {
        lifetime->running = false;
    }
}

void run_threads()
{
    lifetime = init_lifetime_struct();
    pthread_t reader_thread;
    pthread_t analyzer_thread;
    pthread_t printer_thread;
    pthread_t logger_thread;
    pthread_create(&reader_thread, NULL, &reader_func, lifetime);
    pthread_create(&analyzer_thread, NULL, &analyzer_func, lifetime);
    pthread_create(&printer_thread, NULL, &printer_func, lifetime);
    pthread_create(&logger_thread, NULL, &logger_func, lifetime);
    
    pthread_join(reader_thread, NULL);
    pthread_join(analyzer_thread, NULL);
    pthread_join(printer_thread, NULL);
    pthread_join(logger_thread, NULL);
    lifetime_struct_free(lifetime);
}
