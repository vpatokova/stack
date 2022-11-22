#include <assert.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "../include/dump.h"
#include "../include/stack.h"
#include "../include/common.h"

void open_log_file(void)
{
    const char *log_file_path = "../log.txt";

    if (file_status == FILE_CLOSE)
    {
        logs = fopen(log_file_path, "w");

        assert(logs != nullptr && "Could not write to log file\n");

        file_status = FILE_OPEN;
    }

    if (file_status == FILE_CLOSE_ADD)
    {
        logs = fopen(log_file_path, "a");

        assert(logs != nullptr && "Could not write to log file\n");

        file_status = FILE_OPEN;
    }
}

void close_log_file(void)
{
    if (file_status == FILE_OPEN)
    {
        fclose(logs);

        file_status = FILE_CLOSE_ADD;
    }
}

void get_errors (stack *stk)
{
    assert(stk != nullptr);
    
    stk->info.error_code = 0;

    if (stk->data == nullptr)
        stk->info.error_code = stk->info.error_code | NULL_PTR_TO_DATA;

    if (stk->size > stk->capacity)
        stk->info.error_code = stk->info.error_code | SIZE_MORE_THAN_CAPACITY;

    if (stk->size < 0 || stk->capacity < 0)
        stk->info.error_code = stk->info.error_code | SIZE_OR_CAPACITY_NEGATIVE;
}

void stk_dump_release (stack *stk, FILE *log, const char *func, int line, const char *file_name)
{
    assert(log != nullptr && "Could not write to log file\n");
    assert(stk != nullptr);
    assert(func != nullptr);
    assert(file_name != nullptr);

    fprintf(log, "\n%s() at %s(%d)\n", func, file_name, line);
    fprintf(log, "Stack[%p]", stk);

    if (stk->info.error_code == 0)
    {
        fprintf(log, "(ok) \"%s\" at %s() at %s(%d)\n", stk->info.stack_name,
                                                        stk->info.func,
                                                        stk->info.file_name,
                                                        stk->info.line);

        fprintf(log, "size =  %u\n",     stk->size);
        fprintf(log, "capacity =  %u\n", stk->capacity);
        fprintf(log, "data [%p]\n {\n",   stk->data);

        for (unsigned int i = 0; i < stk->capacity; i++)
            if (stk->data[i] == POISON)
                fprintf(log, "[%d] = %g (POISON)\n", i, stk->data[i]);
            else    
                fprintf(log, "[%d] = %g \n", i, stk->data[i]);

        fprintf(log, " }\n");
    }

    else
    {
        fprint_errors(stk, log);
        fprintf(log, "size =  %u\n",     stk->size);
        fprintf(log, "capacity =  %u\n", stk->capacity);
        fprintf(log, "data [%p]\n {\n",   stk->data);
    }
}

void fprint_errors (stack *stk, FILE *log)
{   
    assert(log != nullptr && "Could not write to log file");
    assert(stk != nullptr);

    if (stk->info.error_code & NULL_PTR_TO_DATA)
    {
        fprint_error(stk, log);
        fprintf(log, "NULL POINTER TO DATA\n");
    }

    if (stk->info.error_code & SIZE_MORE_THAN_CAPACITY)
    {
        fprint_error(stk, log);
        fprintf(log, "SIZE MORE THAN CAPACITY\n");
    }

    if (stk->info.error_code & SIZE_OR_CAPACITY_NEGATIVE)
    {
        fprint_error(stk, log);
        fprintf(log, "SIZE OR CAPACITY IS A NEGATIVE NUMBER\n");
    }   
}

void fprint_error(stack *stk, FILE *log)
{
    assert(stk != nullptr);
    assert(log != nullptr);

    fprintf(log, "(ERROR) \"%s\" at %s() at %s(%d)\n", stk->info.stack_name,
                                                        stk->info.func,
                                                        stk->info.file_name,
                                                        stk->info.line);
}