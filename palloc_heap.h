#ifndef _PALLOC_HEAP_GUARD
#define _PALLOC_HEAP_GUARD

#define PALLOC_TARGET_ARM ARM

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>

// block size in bytes
#ifndef BLOCK_SIZE
#define BLOCK_SIZE 8
#endif

// pool size in blocks
#ifndef POOL_SIZE
#define POOL_SIZE 256000
#endif

#if PALLOC_TARGET == PALLOC_TARGET_ARM
// TODO: define lock and unlock mutex for an arm
#endif

#define CHUNK_SIZE 255 // TODO: test corner cases!

// pointer size in target architecture
typedef uintptr_t* header_ptr_t;

/*
    Structure represents chunk header:
    ch_ptr - pointer to the next chunk with available block
    ch_head - offset to the next free block inside a chunk
    n_free_blks - number of free blocks whithin a chunk
 */
typedef struct
{
    header_ptr_t ch_ptr;
    uint8_t ch_head;
    uint8_t n_free_blks;
} chunk_header_t;

typedef struct
{
    chunk_header_t header;
    char data[BLOCK_SIZE * CHUNK_SIZE];
} full_chunk_t;

#define LAST_CHUNK_SIZE POOL_SIZE % CHUNK_SIZE

#if LAST_CHUNK_SIZE > 0 || POOL_SIZE == 1
#define CHUNKS_NUM (POOL_SIZE / CHUNK_SIZE)
#else
#define CHUNKS_NUM (POOL_SIZE / CHUNK_SIZE) + 1
#endif // LAST_CHUNK_SIZE > 0 || POOL_SIZE == 1


void print_sizes();
int palloc_init();
void* palloc_allocate();
void palloc_free(void*);

#endif // _PALLOC_HEAP_GUARD
