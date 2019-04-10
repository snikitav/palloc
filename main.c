#include <stdio.h>
#include <stdlib.h>

#include "palloc_heap.h"

#define N 8

int8_t* a[N];

int main(int argc, char** argv)
{
    printf("main\n");
    int status = palloc_init();

    int8_t* testint = (int8_t*)palloc_allocate();
    int8_t* testint1 = (int8_t*)palloc_allocate();
    int8_t* testint2 = (int8_t*)palloc_allocate();
    int8_t* testint3 = (int8_t*)palloc_allocate();
    int8_t* testint4 = (int8_t*)palloc_allocate();
    int8_t* testint5 = (int8_t*)palloc_allocate();
    int8_t* testint6 = (int8_t*)palloc_allocate();
    int8_t* testint7 = (int8_t*)palloc_allocate();
    // int8_t* testint8 = (int8_t*)palloc_allocate();
    *testint = 42;
    *testint1 = 42;
    *testint2 = 42;
    *testint3 = 42;
    *testint4 = 42;
    *testint5 = 42;
    *testint6 = 42;
    *testint7 = 42;
    // *testint8 = 42;

    palloc_free(testint7);
    palloc_free(testint2);
    palloc_free(testint4);
    palloc_free(testint);
    // palloc_free(testint8);
    palloc_free(testint5);
    palloc_free(testint3);
    palloc_free(testint1);
    palloc_free(testint6);

    testint = (int8_t*)palloc_allocate();
    testint1 = (int8_t*)palloc_allocate();
    testint2 = (int8_t*)palloc_allocate();
    testint3 = (int8_t*)palloc_allocate();
    testint4 = (int8_t*)palloc_allocate();
    testint5 = (int8_t*)palloc_allocate();
    testint6 = (int8_t*)palloc_allocate();
    testint7 = (int8_t*)palloc_allocate();

    *testint = 42;
    *testint1 = 42;
    *testint2 = 42;
    *testint3 = 42;
    *testint4 = 42;
    *testint5 = 42;
    *testint6 = 42;
    *testint7 = 42;

    palloc_free(testint6);
    palloc_free(testint1);
    palloc_free(testint7);
    palloc_free(testint3);
    palloc_free(testint4);
    // palloc_free(testint8);
    palloc_free(testint2);
    palloc_free(testint5);
    palloc_free(testint);

    print_sizes();
}