#include <stdio.h>
#include <string.h>
#include "include/stack.h"
#include "include/debug.h"
#include "include/common.h"
#include "include/log.h"

int main(void) //спросить про очередность компилятор/препроцессор/компилятор?
{
    stack stk1 = {}; //почему не надо обнулять структуры?
    const int capacity = 5; //большие или маленькие буквы?

    stack_ctor(stk1, capacity);

    for (unsigned int count = 1; count <= capacity; count++)
        stack_push(&stk1, count);

    elem_data_t value = 0;

    for (unsigned int count = 1; count <= capacity; count++)
    {
        value = stack_pop(&stk1);
        printf("%g", value);
    }

    stack_dtor(&stk1);

    return 0;
}