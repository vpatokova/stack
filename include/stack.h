#ifndef STACK_H
#define STACK_H

#include "common.h"

typedef double elem_data_t;
#define POISON NAN

 typedef struct
 {
    size_t       capacity;
    size_t       size;
    elem_data_t *data;

    stack_info info;

 } stack;

 typedef struct 
 {
// errors info    
    long int number_of_errors;
// stack info
    int         line;
    const char *func;
    const char *file_name;
    const char *stack_name;
// dump info
    int         line_call;
    const char *func_call;
    const char *file_name_call;

 } stack_info;
 
 

void stack_ctor   (stack *stk, size_t capacity);
void stack_push   (stack *stk, elem_data_t value);
void stack_resize (stack *stk);
void stack_pop    (stack *stk, double *value_ptr);
void stack_dtor   (stack *stk);

#endif // !STACK_H
