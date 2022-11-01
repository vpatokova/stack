#ifndef DEBUG_H
#define DEBUG_H

#include "stack.h"
#include "log.h"
#include <stdio.h>
#include <stdlib.h>

extern FILE *logs; //глобальная переменная?

#define INFO_CALL __FUNCTION__, __LINE__, __FILE__

#define ASSERT(stk) get_errors(stk); to_dump(stk, logs, INFO_CALL);

void to_dump      (stack *stk, FILE *log, const char *func, int line, const char *file_name);
void printf_errors(stack *stk, FILE *log);
void get_errors   (stack *stk);
void printf_error (stack *stk, FILE *log);

#endif // !DEBUG_H