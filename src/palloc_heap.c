#include "palloc_heap.h"

// pointer to free node
static palloc_chunk_t* _p_head = NULL;

// allocatable data
static palloc_chunk_t  _pool[CHUNKS_NUM];

// number of free blocks
static size_t free_blocks = POOL_SIZE;

void palloc_init()
{
    palloc_chunk_t* chunk = _p_head = _pool;

    // build in-place linked list of available chunks
    for(int i = 0; i < CHUNKS_NUM; i++, chunk++)
    {
        chunk->next = (chunk + 1);
        chunk->next_free_block = 0;
        chunk->num_free_blks = CHUNK_SIZE;
        for(int j = 0; j < CHUNK_SIZE; j++)
        {
            uint8_t* data = chunk->data;
            *(data + BLOCK_SIZE * j) = j + 1;
        }
    }

    // last pointer of linked list points to NULL
    (--chunk)->next = NULL;
}

void* palloc_allocate()
{
    if(_p_head == NULL)
    {
        // no space left in a pool
        return NULL;
    }

    free_blocks--;

    palloc_chunk_t* chunk = _p_head;
    uint8_t* block_ptr = chunk->data;

    // calculate offset of next free block in a chunk
    block_ptr = (block_ptr + (BLOCK_SIZE * chunk->next_free_block));
    // set new free block number
    chunk->next_free_block = *block_ptr;
    // delete allocator marks from data
    *block_ptr = 0;

    if(--(chunk->num_free_blks) == 0)
    {
        _p_head = chunk->next;
    }

    return (void*) block_ptr;
}

void palloc_free(void* ptr)
{
    // TODO: check if pointer is allocated in a pool
    if(ptr == NULL)
    {
        return;
    }

    free_blocks++;

    // first, calculate pointer to corresponting chunk
    uintptr_t chunk_size = sizeof(palloc_chunk_t);
    uintptr_t block_uptr = (uintptr_t) ptr;
    uintptr_t pool_uptr = (uintptr_t)_pool;
    uintptr_t diff = block_uptr - pool_uptr;
    palloc_chunk_t* chunk = (palloc_chunk_t*) (block_uptr - (diff % chunk_size));

    // second, calculate block number in chunk data
    uintptr_t data_uptr = (uintptr_t) &chunk->data;
    uintptr_t data_diff = block_uptr - data_uptr;
    uintptr_t block_num = data_diff / BLOCK_SIZE;

    // put in deallocated block info about previous free block
    *(chunk->data + BLOCK_SIZE * block_num) = chunk->next_free_block;
    // put deallocated block number as next free block number
    chunk->next_free_block = block_num;

    if (chunk->num_free_blks++ != 0)
    {
        return;
    }

    chunk->next = _p_head;
    _p_head = chunk;
}

palloc_info_t palloc_get_info()
{
    palloc_info_t info = { BLOCK_SIZE, POOL_SIZE, free_blocks };
    return info;
}
