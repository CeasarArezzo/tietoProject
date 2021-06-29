#include <logger.h>
#include <stdio.h>
#include <lifetime_struct.h>

void* logger_func(void* param)
{
    lifetime_struct* lifetime = param;
    FILE *fp;
    while(lifetime->running)
    {

    }
    return 0;
}

void send_to_logger(char* to_log, lifetime_struct* ltime)
{

}
