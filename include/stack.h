#ifndef STACK_H
#define STACK_H

#include "common.h"
#include <stdio.h>
#include <stdlib.h>

const int MULTIPLE = 2;
typedef double stk_elem_t;

 typedef struct 
 {
// errors info    
    long int error_code;
// stack info
    int         line;
    const char *func;
    const char *file_name;
    const char *stack_name;
// dump info
    /*int         line_call;
    const char *func_call;
    const char *file_name_call;*/

 } stack_info;

 typedef struct
 {
    int         capacity;
    size_t      size;
    stk_elem_t *data;

    stack_info info;

 } stack; 

#if MODE != MODE_RELEASE
void stack_ctor_ (stack *stk, int capacity, const char *func, int line, const char *file_name);
#else
void stack_ctor_ (stack *stk, int capacity);
#endif

void stack_push       (stack *stk, stk_elem_t value);
void stack_resize     (stack *stk);
void stack_dtor       (stack *stk);
void stack_add        (stack *stk);
void stack_sub        (stack *stk);
void stack_mult       (stack *stk);
void stack_div        (stack *stk);
void stack_out        (stack *stk);
void stack_pop (stack *stk, stk_elem_t *value_ptr);

#define POISON 0x77

#if MODE != MODE_RELEASE
#define INFO_STACK __FUNCTION__, __LINE__, __FILE__
#define stack_ctor(stk, capacity) stk.info.stack_name = #stk; stack_ctor_(&stk, capacity, INFO_STACK);

#else
#define stack_ctor(stk, capacity) stack_ctor_(&stk, capacity);
#endif

#endif // !STACK_H
