#ifndef LOG_H
#define LOG_H

#include <stdio.h>

enum File_status
{
    FILE_OPEN      = 0,
    FILE_CLOSE     = 1,
    FILE_CLOSE_ADD = 2
};

FILE *logs;
File_status file_status = FILE_CLOSE;

void open_log_file(void);

#endif // !LOG_H