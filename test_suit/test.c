#include "test.h"
#include "assert.h"

static uintptr_t* ptrs[POOL_SIZE];

void consecutive_test()
{
    for(int i = 0; i < POOL_SIZE; i++)
    {
        ptrs[i] = (uintptr_t*) palloc_allocate();
        uintptr_t* ptr = ptrs[i];
        *ptr = 42000;
    }

    for(int i = 0; i < POOL_SIZE; i++)
    {
        uintptr_t* ptr = ptrs[i];
        assert(*ptr == 42000);
        *ptr = 43000;
        palloc_free(ptr);
    }

    printf("Consecutive test success\n");
}

void random_test()
{
    time_t t;
    srand((unsigned) time(&t));

    for(int i = 0; i < POOL_SIZE; i++)
    {
        ptrs[i] = (uintptr_t*) palloc_allocate();
        uintptr_t* ptr = ptrs[i];
        *ptr = 42000;
    }

    for(int i = 0; i < POOL_SIZE; i++)
    {
        int rnd = (POOL_SIZE - 1 - i) ? rand() % (POOL_SIZE - 1 - i) : 0;
        uintptr_t* ptr = ptrs[rnd];
        assert(*ptr == 42000);
        palloc_free(ptr);
        uintptr_t* tmp = ptrs[POOL_SIZE - 1 - i];
        ptrs[POOL_SIZE - 1 - i] = ptrs[rnd];
        ptrs[rnd] = tmp;
    }

    printf("Random dealloc test success\n");

}

int main(int argc, char** argv)
{
    palloc_init();

    for(int i = 0; i < 100; i++)
    {
        consecutive_test();
    }

    for(int i = 0; i < 100; i++)
    {
        random_test();
    }

    return 0;
}