#ifndef PALLOC_TEST
#define PALLOC_TEST

#include "palloc_heap.h"

#include <time.h>
#include <limits.h>

#if BLOCK_SIZE >= 8
#define check_t uint64_t
#define PALLOC_TEST_MAX_VAL ULONG_MAX
#elif BLOCK_SIZE >= 4
#define check_t uint32_t
#define PALLOC_TEST_MAX_VAL UINT_MAX
#elif BLOCK_SIZE >= 2
#define check_t uint16_t
#define PALLOC_TEST_MAX_VAL USHRT_MAX
#else
#define check_t uint8_t
#define PALLOC_TEST_MAX_VAL UCHAR_MAX
#endif

typedef struct
{
    check_t* ptr;
    check_t check_val;
} test_struct_t;

#endif // PALLOC_TEST
