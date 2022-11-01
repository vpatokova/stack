#include <assert.h>
#include <stdio.h>
#include "../include/stack.h"
#include "../include/debug.h"
#include "../include/common.h"
#include "../include/log.h"

void open_log_file(void)
{
    const char *log_file_path = "../log.txt";

    if (file_status == FILE_CLOSE)
    {
        logs = fopen(log_file_path, "w");

        assert(logs != nullptr && "Could not open log file\n");

        file_status = FILE_OPEN;
    }

    if (file_status == FILE_CLOSE_ADD)
    {
        logs = fopen(log_file_path, "a");

        assert(logs != nullptr && "Could not open log file\n");

        file_status = FILE_OPEN;
    }
}