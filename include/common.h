#ifndef COMMON_H
#define COMMON_H

enum Stack_errors
{
    NULL_PTR_TO_DATA          = 1 << 0,
    SIZE_MORE_THAN_CAPACITY   = 1 << 1,
    SIZE_OR_CAPACITY_NEGATIVE = 1 << 2
};

#define MODE_RELEASE        1 
#define MODE_CANARY_ON      2
#define MODE_HASH_ON        3
#define MODE_HASH_CANARY_ON 4

#ifdef RELEASE
    #define MODE MODE_RELEASE
#endif

#ifdef CANARY_ON
    #define MODE MODE_CANARY_ON
#endif

#ifdef HASH_ON
    #define MODE MODE_HASH_ON
#endif

#ifdef DEBUG
    #define MODE MODE_HASH_CANARY_ON
#endif

#endif // !COMMMON_H