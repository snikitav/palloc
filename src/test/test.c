#include "test.h"

static test_struct_t tests[POOL_SIZE];

void consecutive_test()
{
    for(int i = 0; i < POOL_SIZE; i++)
    {
        tests[i].ptr = (check_t*) palloc_allocate();
        check_t check = rand() % PALLOC_TEST_MAX_VAL;
        *tests[i].ptr = check;
        tests[i].check_val = check;
    }

    for(int i = 0; i < POOL_SIZE; i++)
    {
        if(*tests[i].ptr != tests[i].check_val)
        {
            perror("Consecutive test failed on dealloc\n");
            exit(1);
        }
        palloc_free(tests[i].ptr);
    }
}

void random_test()
{
    for(int i = 0; i < POOL_SIZE; i++)
    {
        tests[i].ptr = (check_t*) palloc_allocate();
        check_t check = rand() % PALLOC_TEST_MAX_VAL;
        *tests[i].ptr = check;
        tests[i].check_val = check;
    }

    const int psmo = POOL_SIZE - 1;

    for(int i = 0; i < POOL_SIZE; i++)
    {
        int rnd = (psmo - i) ? rand() % (psmo - i) : 0;
        if(*tests[rnd].ptr != tests[rnd].check_val)
        {
            perror("Random test failed on dealloc\n");
            exit(1);
        }
        palloc_free(tests[rnd].ptr);

        test_struct_t tmp = tests[psmo - i];
        tests[psmo - i] = tests[rnd];
        tests[rnd] = tmp;
    }
}

int main(int argc, char** argv)
{
    time_t t;
    srand((unsigned) time(&t));

    palloc_init();

    for(int i = 0; i < 100; i++)
    {
        consecutive_test();
    }
    printf("Consecutive test success\n");

    for(int i = 0; i < 100; i++)
    {
        random_test();
    }
    printf("Random dealloc test success\n");

    return 0;
}