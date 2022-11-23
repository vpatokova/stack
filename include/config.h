#ifndef CONFIG_H
#define CONFIG_H

enum Stack_errors
{
    NULL_PTR_TO_DATA          = 1 << 0,
    SIZE_MORE_THAN_CAPACITY   = 1 << 1,
    SIZE_OR_CAPACITY_NEGATIVE = 1 << 2
};

#endif // !CONFIG_H