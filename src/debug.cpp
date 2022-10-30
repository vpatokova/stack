#include <assert.h>
#include <math.h>
#include "../include/debug.h"
#include "../include/log.h"
#include "../include/stack.h"

void to_dump (stack *stk, FILE *log, const char *func, int line, const char *file_name)
{
    assert(log != nullptr && "Could not open log file\n");

    stk->info.line_call = line;
    stk->info.file_name_call = file_name;
    stk->info.func_call = func;

    fprintf(log, "\n%s() at %s(%d)\n", func, file_name, line);
    fprintf(log, "Stack[%p]", stk);

    if (stk->info.number_of_errors == 0)
    {
        fprintf(log, "(ok) \"%s\" at %s() at %s(%d)\n", stk->info.stack_name,
                                                        stk->info.func,
                                                        stk->info.file_name,
                                                        stk->info.line);

        fprintf(log, "size =  %lu\n",     stk->size);
        fprintf(log, "capacity =  %lu\n", stk->capacity);
        fprintf(log, "data [%p]\n {\n",   stk->data);

        for (int i = 0; i < stk->capacity; i++)
            if (isnan(stk->data[i]))
                fprintf(log, "[%d] = %g (POIZON)\n", i, stk->data[i]);
            else    
                fprintf(log, "[%d] = %g \n", i, stk->data[i]);

        fprintf(log, " }\n");
    }

    else
    {
        //printf_errors(stk, log);
        fprintf(log, "size =  %lu\n",     stk->size);
        fprintf(log, "capacity =  %lu\n", stk->capacity);
        fprintf(log, "data [%p]\n {\n",   stk->data);
    }
}

