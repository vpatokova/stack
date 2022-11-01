#include <assert.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "../include/debug.h"
#include "../include/log.h"
#include "../include/stack.h"

void get_errors (stack *stk)
{
    stk->info.error_code = 0;

    if (stk == nullptr)
        stk->info.error_code = stk->info.error_code | (1 << NULL_PTR_TO_STACK);

    if (stk->data == nullptr)
        stk->info.error_code = stk->info.error_code | (1 << NULL_PTR_TO_DATA);

    if (stk->size > stk->capacity)
        stk->info.error_code = stk->info.error_code | (1 << SIZE_MORE_THAN_CAPACITY);

    if (stk->size < 0 || stk->capacity < 0)
        stk->info.error_code = stk->info.error_code | (1 << SIZE_OR_CAPACITY_NEGATIVE);
}

void to_dump (stack *stk, FILE *log, const char *func, int line, const char *file_name)
{
    assert(log != nullptr && "Could not open log file\n");

    /*stk->info.line_call = line;
    stk->info.file_name_call = file_name;
    stk->info.func_call = func;*/

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
            if (isnan(stk->data[i]))
                fprintf(log, "[%d] = %g (POISON)\n", i, stk->data[i]);
            else    
                fprintf(log, "[%d] = %g \n", i, stk->data[i]);

        fprintf(log, " }\n");
    }

    else
    {
        printf_errors(stk, log);
        fprintf(log, "size =  %u\n",     stk->size);
        fprintf(log, "capacity =  %u\n", stk->capacity);
        fprintf(log, "data [%p]\n {\n",   stk->data);
    }
}

void printf_errors (stack *stk, FILE *log)
{
    if ((stk->info.error_code << NULL_PTR_TO_STACK) & 1)
    {
        printf_error(stk, log);
        fprintf(log, "NULL POINTER TO STACK\n");
    }

    if ((stk->info.error_code << NULL_PTR_TO_DATA) & 1)
    {
        printf_error(stk, log);
        fprintf(log, "NULL POINTER TO DATA\n");
    }

    if ((stk->info.error_code << SIZE_MORE_THAN_CAPACITY) & 1)
    {
        printf_error(stk, log);
        fprintf(log, "SIZE MORE THAN CAPACITY\n");
    }

    if ((stk->info.error_code << SIZE_OR_CAPACITY_NEGATIVE) & 1)
    {
        printf_error(stk, log);
        fprintf(log, "SIZE OR CAPACITY IS A NEGATIVE NUMBER\n");
    }   
}

void printf_error(stack *stk, FILE *log)
{
    fprintf(log, "(ERROR) \"%s\" at %s() at %s(%d)\n", stk->info.stack_name,
                                                        stk->info.func,
                                                        stk->info.file_name,
                                                        stk->info.line);
}