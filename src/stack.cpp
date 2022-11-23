#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <assert.h>
#include "../include/stack.h"
#include "../include/dump.h"
#include "../include/config.h"

static void poison_data(stack *stk);

#ifdef DEBUG
void stack_ctor_(stack *stk, int capacity, const char *func, int line, const char *file_name)
#else
void stack_ctor_(stack *stk, int capacity)
#endif
{
    assert(stk != nullptr);
    assert(capacity > 0 && "Capacity is negative");

    #ifdef DEBUG
        stk->info.func = func;
        stk->info.line = line;
        stk->info.file_name = file_name;
    #endif

    stk->capacity = capacity;

    stk->size = 0;

    stk->data = (stk_elem_t *) calloc(stk->capacity, sizeof(stk_elem_t));

    assert(stk->data != nullptr && "Null pointer to data");

    #ifdef DEBUG
    STK_DUMP(stk);
    #endif
}

void stack_push(stack *stk, stk_elem_t value)
{
    assert(stk != nullptr);

    #ifdef DEBUG
    STK_DUMP(stk);
    #endif

    if (stk->size >= stk->capacity)
        stack_resize(stk);

    stk->data[stk->size++] = value;

    #ifdef DEBUG
    STK_DUMP(stk);
    #endif
}

void stack_resize(stack *stk)
{
    assert(stk != nullptr);
    
    #ifdef DEBUG
    STK_DUMP(stk);
    #endif

    if (stk->size >= stk->capacity)
        stk->capacity *= MUL_BY;

    else if (stk->size + 1 == stk->capacity/MUL_BY)
        stk->capacity /= MUL_BY;

    stk->data = (stk_elem_t *) realloc(stk->data, stk->capacity * sizeof(stk_elem_t));

    poison_data(stk);

    #ifdef DEBUG
    STK_DUMP(stk);
    #endif
}

static void poison_data(stack *stk)
{
    assert(stk != nullptr);

    for (unsigned i = stk->size; i < stk->capacity; i++)
        stk->data[i] = POISON;
}

void stack_pop(stack *stk, stk_elem_t *value_ptr)
{
    #ifdef DEBUG
    STK_DUMP(stk);
    #endif

    assert(stk != nullptr);
    assert(value_ptr != nullptr);

    *value_ptr = stk->data[--(stk->size)];
    
    stk->data[stk->size] = POISON;

    if (stk->size + 1 == stk->capacity/MUL_BY && stk->size >= 10)
        stack_resize(stk);

    #ifdef DEBUG
    STK_DUMP(stk);
    #endif
}

void stack_dtor(stack *stk)
{
    #ifdef DEBUG
    STK_DUMP(stk);
    #endif

    assert(stk != nullptr);

    free(stk->data);

    stk->data = nullptr;
    stk->capacity = -1;
    stk->size = -1;
}

int collect_errors (stack *stk)
{
    assert(stk != nullptr);
    
    int error_code = 0;

    if (stk->data == nullptr)
        error_code = error_code | NULL_PTR_TO_DATA;

    if (stk->size > stk->capacity)
        error_code = error_code | SIZE_MORE_THAN_CAPACITY;

    if (stk->size < 0 || stk->capacity < 0)
        error_code = error_code | SIZE_OR_CAPACITY_NEGATIVE;

    return error_code;
}