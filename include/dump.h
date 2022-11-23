#ifndef DUMP_H
#define DUMP_H

#include "stack.h"
#include <stdio.h>
#include <stdlib.h>

extern FILE *logs;

void open_log_file (void);
void close_log_file(void);

#define INFO_CALL __FUNCTION__, __LINE__, __FILE__

#define STK_DUMP(stk) stk_dump(stk, logs, INFO_CALL);

void stk_dump (stack *stk, FILE *log, const char *func, int line, const char *file_name);

#endif // !DUMP_H