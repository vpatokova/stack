#ifndef STACK_H
#define STACK_H

#include "common.h"
#include <stdio.h>
#include <stdlib.h>

const int MULTIPLE = 2;
typedef double elem_data_t;

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
    size_t       capacity;
    size_t       size;
    elem_data_t *data;

    stack_info info;

 } stack; 

void stack_ctor_      (stack *stk, size_t capacity, const char *func, int line, const char *file_name);
void stack_push       (stack *stk, elem_data_t value);
void stack_resize     (stack *stk);
void stack_dtor       (stack *stk);
void stack_add        (stack *stk);
void stack_sub        (stack *stk);
void stack_mult       (stack *stk);
void stack_div        (stack *stk);
void stack_out        (stack *stk);
elem_data_t stack_pop (stack *stk);

#define POISON NAN
#define INFO_STACK __FUNCTION__, __LINE__, __FILE__ // или лучше __func__?
#define stack_ctor(stk, capacity) stk->info.stack_name = #stk; stack_ctor_(&stk, capacity, INFO_STACK);

#endif // !STACK_H
