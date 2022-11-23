#ifndef STACK_H
#define STACK_H

#include "config.h"
#include <stdio.h>
#include <stdlib.h>

const int MUL_BY = 2;
typedef double stk_elem_t;

 typedef struct 
 {
    int         line;
    const char *func;
    const char *file_name;
    const char *stack_name;

 } stack_info;

 typedef struct
 {
    int         capacity;
    size_t      size;
    stk_elem_t *data;

    stack_info info;

 } stack; 

#ifdef DEBUG
void stack_ctor_ (stack *stk, int capacity, const char *func, int line, const char *file_name);
#else
void stack_ctor_ (stack *stk, int capacity);
#endif

void stack_push   (stack *stk, stk_elem_t value);
void stack_pop    (stack *stk, stk_elem_t *value_ptr);
void stack_resize (stack *stk);
void stack_dtor   (stack *stk);
int collect_errors   (stack *stk);

#define POISON 0x77

#ifdef DEBUG
    #define INFO_STACK __FUNCTION__, __LINE__, __FILE__
    #define stack_ctor(stk, capacity) {stk.info.stack_name = #stk; stack_ctor_(&stk, capacity, INFO_STACK);}

#else
    #define stack_ctor(stk, capacity) stack_ctor_(&stk, capacity);
#endif

#endif // !STACK_H
