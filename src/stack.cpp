#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <assert.h>
#include "../include/stack.h"
#include "../include/debug.h"
#include "../include/common.h"
#include "../include/log.h"

static void poison_data(stack *stk);

void stack_ctor_(stack *stk, size_t capacity, const char *func, int line, const char *file_name)
{
    open_log_file();

    stk->info.func = func;
    stk->info.line = line;
    stk->info.file_name = file_name;

    stk->capacity = capacity;

    stk->size = 0;

    stk->data = (elem_data_t *) calloc(stk->capacity, sizeof(elem_data_t));

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

    if (stk->size >= stk->capacity)
        stk->capacity *= MULTIPLE;

    else if (stk->size + 1 == stk->capacity/MULTIPLE)
        stk->capacity /= MULTIPLE;

    stk->data = (elem_data_t *) realloc(stk->data, stk->capacity * sizeof(elem_data_t));

    poison_data(stk);

    ASSERT(stk);
}

static void poison_data(stack *stk)
{
    for (unsigned int i = stk->size; i < stk->capacity; i++)
        stk->data[i] = POISON;
}

void stack_add(stack *stk)
{
    ASSERT(stk);

    assert(stk->size > 1 && "Not enough values in stack\n");

    elem_data_t value1 = stack_pop(stk);
    elem_data_t value2 = stack_pop(stk);

    stack_push(stk, value1 + value2);

    ASSERT(stk);
}

void stack_sub(stack *stk)
{
    ASSERT(stk);

    assert(stk->size > 1 && "Not enough values in stack\n");

    elem_data_t value1 = stack_pop(stk);
    elem_data_t value2 = stack_pop(stk);

    stack_push(stk, value2 - value1);

    ASSERT(stk);
}

void stack_mult(stack *stk)
{
    ASSERT(stk);

    assert(stk->size > 1 && "Not enough values in stack\n");

    elem_data_t value1 = stack_pop(stk);
    elem_data_t value2 = stack_pop(stk);

    stack_push(stk, value2 * value1);

    ASSERT(stk);
}

void stack_div(stack *stk)
{
    ASSERT(stk);

    assert(stk->size > 1 && "Not enough values in stack\n");

    elem_data_t value1 = stack_pop(stk);
    elem_data_t value2 = stack_pop(stk);

    assert(value1 != 0 && "Can not divide by zero\n");

    stack_push(stk, value2 / value1);

    ASSERT(stk);
}

void stack_out(stack *stk)
{
    ASSERT(stk);

    elem_data_t value = stk->data[--stk->size];
    
    stk->data[stk->size] = POISON;

    if (stk->size + 1 == stk->capacity/MULTIPLE && stk->size >= 10)
        stack_resize(stk);

    ASSERT(stk);

    printf("%lg", value);
}

elem_data_t stack_pop(stack *stk)
{
    ASSERT(stk);

    elem_data_t value = stk->data[--stk->size];
    
    stk->data[stk->size] = POISON;

    if (stk->size + 1 == stk->capacity/MULTIPLE && stk->size >= 10)
        stack_resize(stk);

    ASSERT(stk);

    return value;
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
        fclose(logs);

        file_status = FILE_CLOSE_ADD;
    }
}