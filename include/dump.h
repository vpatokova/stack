#ifndef DUMP_H
#define DUMP_H

#include "stack.h"
#include <stdio.h>
#include <stdlib.h>

enum File_status
{
    FILE_OPEN      = 0,
    FILE_CLOSE     = 1,
    FILE_CLOSE_ADD = 2
};

FILE *logs;
File_status file_status = FILE_CLOSE;

void open_log_file (void);
void close_log_file(void);

#define INFO_CALL __FUNCTION__, __LINE__, __FILE__

#define ASSERT(stk) {get_errors(stk); stk_dump_release(stk, logs, INFO_CALL);}

void stk_dump_release (stack *stk, FILE *log, const char *func, int line, const char *file_name);
void fprint_errors(stack *stk, FILE *log);
void get_errors   (stack *stk);
void fprint_error (stack *stk, FILE *log);

#endif // !DUMP_H