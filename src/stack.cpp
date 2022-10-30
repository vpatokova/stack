#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "../include/stack.h"
#include "../include/debug.h"
#include "../include/common.h"
#include "../include/log.h"

void stack_ctor(stack *stk, size_t capacity)
{
    open_log_file();

    stk->capacity = capacity;

    stk->size = 0;

    ASSERT(stk);
}

void stack_push(stack *stk, elem_data_t value)
{
    ASSERT(stk);

    if (stk->size >= stk->capacity)
        stack_resize(stk);

    stk->data[stk->size++] = value;

    ASSERT(stk);
}

void stack_resize(stack *stk)
{
    ASSERT(stk);

    stk->data = (double *) realloc(stk->data, stk->capacity * sizeof(double));

    poison_data(stk);

    ASSERT(stk);
}

static void poison_data(stack *stk)
{
    for (int i = stk->size; i < stk->capacity; i++)
        stk->data[i] = POISON;
}

void stack_pop(stack *stk, double *value_ptr)
{
    ASSERT(stk);

    *value_ptr = stk->data[stk->size--]; //спросить у Лизы почему
    
    stk->data[stk->size] = NAN;

    if //что-то там
        stack_resize(stk);

    ASSERT(stk);
}


void stack_dtor(stack *stk)
{
    ASSERT(stk);

    free(stk->data);

    stk->data = nullptr;
    stk->capacity = -1;
    stk->size = -1;

    if (file_status == FILE_OPEN)
    {
        fclose(logs_);

        file_status = FILE_CLOSE_ADD;
    }
}