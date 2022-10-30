#ifndef DEBUG_H
#define DEBUG_H

#define INFO_CALL __FUNCTION__, __LINE__, __FILE__

#define ASSERT(stk) to_dump(stk, logs_, INFO_CALL);

extern FILE *logs_;

void to_dump      (stack *stk, FILE *log, const char *func, int line, const char *file_name);
void printf_errors(stack *stk, FILE *log);
void assert_ok    (stack *stk);
void printf_error (stack *stk, FILE *log);

#endif // !DEBUG_H