#ifndef _PALLOC_HEAP_GUARD
#define _PALLOC_HEAP_GUARD

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

#define CHUNK_SIZE 255

/*
    Structure represents:
    block_size - block size in bytes
    pool_size - pool size in blocks
    free_blocks - number of free blocks available
 */
typedef struct
{
    int block_size;
    int pool_size;
    int free_blocks;
} palloc_info_t;

/*
    Structure represents whole chunk of blocks:
    next - pointer to the next chunk with available block
    next_free_block - offset to the next free block inside a chunk
    num_free_blks - number of free blocks whithin a chunk
    data - array of blocks whithin a chunk
*/
typedef struct palloc_chunk
{
    struct palloc_chunk* next;
    uint8_t next_free_block;
    uint8_t num_free_blks;
    uint8_t data[BLOCK_SIZE * CHUNK_SIZE];
} palloc_chunk_t;

#define LAST_CHUNK_SIZE (POOL_SIZE % CHUNK_SIZE)

#if (POOL_SIZE < CHUNK_SIZE) || LAST_CHUNK_SIZE
#define CHUNKS_NUM ((POOL_SIZE / CHUNK_SIZE) + 1)
#else
#define CHUNKS_NUM (POOL_SIZE / CHUNK_SIZE)
#endif // (POOL_SIZE < CHUNK_SIZE) || LAST_CHUNK_SIZE

void palloc_init();
void* palloc_allocate();
void palloc_free(void*);
palloc_info_t palloc_get_info();

#endif // _PALLOC_HEAP_GUARD
