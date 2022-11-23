#include <assert.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "../include/dump.h"
#include "../include/stack.h"
#include "../include/config.h"

FILE *log = NULL;

void fprint_errors(stack *stk, int error_code);
void fprint_error (stack *stk);

void stk_dump (stack *stk, FILE *log, const char *func, int line, const char *file_name)
{
    assert(log != nullptr && "Could not write to log file\n");
    assert(stk != nullptr);
    assert(func != nullptr);
    assert(file_name != nullptr);

    int error_code = collect_errors(stk);

    fprintf(log, "\n%s() at %s(%d)\n", func, file_name, line);
    fprintf(log, "Stack[%p]", stk);

    if (error_code == 0)
    {
        fprintf(log, "(ok) \"%s\" at %s() at %s(%d)\n", stk->info.stack_name,
                                                        stk->info.func,
                                                        stk->info.file_name,
                                                        stk->info.line);

        fprintf(log, "size =  %u\n",     stk->size);
        fprintf(log, "capacity =  %u\n", stk->capacity);
        fprintf(log, "data [%p]\n {\n",   stk->data);

        for (unsigned i = 0; i < stk->capacity; i++)
            if (stk->data[i] == POISON)
                fprintf(log, "[%d] = %g (POISON)\n", i, stk->data[i]);
            else    
                fprintf(log, "[%d] = %g \n", i, stk->data[i]);

        fprintf(log, " }\n");
    }

    else
    {
        fprint_errors(stk, error_code);
        fprintf(log, "size =  %u\n",     stk->size);
        fprintf(log, "capacity =  %u\n", stk->capacity);
        fprintf(log, "data [%p]\n {\n",   stk->data);
    }
}

void fprint_errors (stack *stk, int error_code)
{   
    assert(stk != nullptr);

    if (error_code & NULL_PTR_TO_DATA)
    {
        fprint_error(stk);
        fprintf(log, "NULL POINTER TO DATA\n");
    }

    if (error_code & SIZE_MORE_THAN_CAPACITY)
    {
        fprint_error(stk);
        fprintf(log, "SIZE MORE THAN CAPACITY\n");
    }

    if (error_code & SIZE_OR_CAPACITY_NEGATIVE)
    {
        fprint_error(stk);
        fprintf(log, "SIZE OR CAPACITY IS A NEGATIVE NUMBER\n");
    }   
}

void fprint_error(stack *stk)
{
    assert(stk != nullptr);

    fprintf(log, "(ERROR) \"%s\" at %s() at %s(%d)\n", stk->info.stack_name,
                                                       stk->info.func,
                                                       stk->info.file_name,
                                                       stk->info.line);
}

void open_log_file(void)
{
    const char *const LOG_FILE_PATH = "./log.txt";

    log = fopen(LOG_FILE_PATH, "w");

    assert(log != nullptr && "Could not write to log file\n");
}

void close_log_file(void)
{
    fclose(log);
}