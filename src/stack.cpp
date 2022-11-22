#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <assert.h>
#include "../include/stack.h"
#include "../include/dump.h"
#include "../include/common.h"

static void poison_data(stack *stk);

#if MODE != MODE_RELEASE
void stack_ctor_(stack *stk, int capacity, const char *func, int line, const char *file_name)
#else
void stack_ctor_(stack *stk, int capacity)
#endif
{
    assert(stk != nullptr);
    assert(capacity > 0 && "Capacity is negative");

    #if MODE != MODE_RELEASE
        stk->info.func = func;
        stk->info.line = line;
        stk->info.file_name = file_name;
    #endif

    stk->capacity = capacity;

    stk->size = 0;

    stk->data = (stk_elem_t *) calloc(stk->capacity, sizeof(stk_elem_t));

    #if MODE != MODE_RELEASE
    ASSERT(stk);
    #endif
}

void stack_push(stack *stk, stk_elem_t value)
{
    assert(stk != nullptr);

    #if MODE != MODE_RELEASE
    ASSERT(stk);
    #endif

    if (stk->size >= stk->capacity)
        stack_resize(stk);

    stk->data[stk->size++] = value;

    #if MODE != MODE_RELEASE
    ASSERT(stk);
    #endif
}

void stack_resize(stack *stk)
{
    assert(stk != nullptr);
    
    #if MODE != MODE_RELEASE
    ASSERT(stk);
    #endif

    if (stk->size >= stk->capacity)
        stk->capacity *= MULTIPLE;

    else if (stk->size + 1 == stk->capacity/MULTIPLE)
        stk->capacity /= MULTIPLE;

    stk->data = (stk_elem_t *) realloc(stk->data, stk->capacity * sizeof(stk_elem_t));

    poison_data(stk);

    #if MODE != MODE_RELEASE
    ASSERT(stk);
    #endif
}

static void poison_data(stack *stk)
{
    assert(stk != nullptr);

    for (unsigned i = stk->size; i < stk->capacity; i++)
        stk->data[i] = POISON;
}

void stack_add(stack *stk)
{
    #if MODE != MODE_RELEASE
    ASSERT(stk);
    #endif

    assert(stk != nullptr);
    assert(stk->size > 1 && "Not enough values in stack\n");

    stk_elem_t value1 = 0;
    stk_elem_t value2 = 0;

    stack_pop(stk, &value1);
    stack_pop(stk, &value2);

    stack_push(stk, value1 + value2);

    #if MODE != MODE_RELEASE
    ASSERT(stk);
    #endif
}

void stack_sub(stack *stk)
{
    #if MODE != MODE_RELEASE
    ASSERT(stk);
    #endif

    assert(stk != nullptr);
    assert(stk->size > 1 && "Not enough values in stack\n");

    stk_elem_t value1 = 0;
    stk_elem_t value2 = 0;

    stack_pop(stk, &value1);
    stack_pop(stk, &value2);

    stack_push(stk, value2 - value1);

    #if MODE != MODE_RELEASE
    ASSERT(stk);
    #endif
}

void stack_mult(stack *stk)
{
    #if MODE != MODE_RELEASE
    ASSERT(stk);
    #endif

    assert(stk != nullptr);
    assert(stk->size > 1 && "Not enough values in stack\n");

    stk_elem_t value1 = 0;
    stk_elem_t value2 = 0;

    stack_pop(stk, &value1);
    stack_pop(stk, &value2);

    stack_push(stk, value2 * value1);

    #if MODE != MODE_RELEASE
    ASSERT(stk);
    #endif
}

void stack_div(stack *stk)
{
    #if MODE != MODE_RELEASE
    ASSERT(stk);
    #endif

    assert(stk != nullptr);
    assert(stk->size > 1 && "Not enough values in stack\n");

    stk_elem_t value1 = 0;
    stk_elem_t value2 = 0;

    stack_pop(stk, &value1);
    stack_pop(stk, &value2);

    assert(value1 != 0 && "Can not divide by zero\n");

    stack_push(stk, value2 / value1);

    #if MODE != MODE_RELEASE
    ASSERT(stk);
    #endif
}

void stack_out(stack *stk)
{
    #if MODE != MODE_RELEASE
    ASSERT(stk);
    #endif

    assert(stk != nullptr);
    stk_elem_t value = stk->data[--stk->size];
    
    stk->data[stk->size] = POISON;

    if (stk->size + 1 == stk->capacity/MULTIPLE && stk->size >= 10)
        stack_resize(stk);

    #if MODE != MODE_RELEASE
    ASSERT(stk);
    #endif

    printf("%lg", value);
}

void stack_pop(stack *stk, stk_elem_t *value_ptr)
{
    #if MODE != MODE_RELEASE
    ASSERT(stk);
    #endif

    assert(stk != nullptr);
    assert(value_ptr != nullptr);

    *value_ptr = stk->data[--(stk->size)];
    
    stk->data[stk->size] = POISON;

    if (stk->size + 1 == stk->capacity/MULTIPLE && stk->size >= 10)
        stack_resize(stk);

    #if MODE != MODE_RELEASE
    ASSERT(stk);
    #endif
}


void stack_dtor(stack *stk)
{
    #if MODE != MODE_RELEASE
    ASSERT(stk);
    #endif

    assert(stk != nullptr);

    free(stk->data);

    stk->data = nullptr;
    stk->capacity = -1;
    stk->size = -1;
}