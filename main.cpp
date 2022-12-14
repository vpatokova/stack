#include <stdio.h>
#include <string.h>
#include "include/stack.h"
#include "include/dump.h"
#include "include/config.h"

int main(void)
{
    stack stk1 = { 0 };
    const int CAPACITY = 5;

    #ifdef MODE_DEBUG
        open_log_file();
    #endif
    
    stack_ctor(stk1, CAPACITY);

    for (unsigned count = 1; count <= CAPACITY; count++)
        stack_push(&stk1, count);

    stk_elem_t value = 0;

    for (unsigned count = 1; count <= CAPACITY; count++)
    {
        stack_pop(&stk1, &value);
        printf("%g", value);
    }

    stack_dtor(&stk1);
    
    #ifdef MODE_DEBUG
        close_log_file();
    #endif

    return 0;
}