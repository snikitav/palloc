#include "palloc_heap.h"

// free node
static chunk_header_t* _p_head = NULL;
// allocatable data
static uint8_t  _pool[(POOL_SIZE * BLOCK_SIZE) + (sizeof(chunk_header_t) * CHUNKS_NUM)];

static size_t free_blocks = POOL_SIZE;

void palloc_init()
{
    full_chunk_t* chunk = (full_chunk_t *) _pool;
    _p_head = &chunk->header;

    // build in-place linked list of available chunks
    for(int i = 0; i <= CHUNKS_NUM; i++, chunk++)
    {
        chunk->header.ch_ptr = (i != CHUNKS_NUM) ? (header_ptr_t)(chunk + 1) : NULL;
        chunk->header.ch_head = 0;
        int chunk_size = (i != CHUNKS_NUM) ? CHUNK_SIZE : LAST_CHUNK_SIZE;
        for(int j = 0; j < chunk_size; j++)
        {
            uint8_t* data = chunk->data;
            *(data + BLOCK_SIZE * j) = j + 1; // possible error, test it!
        }

        chunk->header.n_free_blks = chunk_size;
    }
}

void* palloc_allocate()
{
    if(_p_head == NULL)
    {
        // no space left in a pool
        return NULL;
    }

    full_chunk_t* chunk = (full_chunk_t*) _p_head;
    uint8_t* block_ptr = chunk->data;


    block_ptr = (block_ptr + (BLOCK_SIZE * chunk->header.ch_head));
    chunk->header.ch_head = *block_ptr;

    // delete allocator marks from data
    *block_ptr = 0;

    if(--(chunk->header.n_free_blks) == 0)
    {
        _p_head = (chunk_header_t*)_p_head->ch_ptr;
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

    // first, calculate block num for a given ponter
    uintptr_t full_chunk_size = sizeof(full_chunk_t);
    uintptr_t block_uptr = (uintptr_t) ptr;
    uintptr_t pool_uptr = (uintptr_t)_pool;
    uintptr_t diff = block_uptr - pool_uptr;
    uintptr_t block_num = (diff % full_chunk_size - sizeof(chunk_header_t)) / BLOCK_SIZE;
    // second, find out pointer to corresponding chunk
    full_chunk_t* chunk = (full_chunk_t*)(block_uptr - (block_num * BLOCK_SIZE) - sizeof(chunk_header_t));

    uint8_t* data = chunk->data;
    *(data + BLOCK_SIZE * block_num) = chunk->header.ch_head;
    chunk->header.ch_head = block_num;

    if (chunk->header.n_free_blks++ != 0)
    {
        return;
    }

    chunk->header.ch_ptr = (header_ptr_t)_p_head;
    _p_head = &chunk->header;
}

// Debug info, to be deleted
void print_sizes()
{
    printf("Block size: %d\n", BLOCK_SIZE);
    printf("Pool size: %d\n", POOL_SIZE);

    chunk_header_t* _local_p_head = _p_head;

    int i = 0;
    do
    {
        int j;
        for(j = 0; j < _local_p_head->n_free_blks; j++)
        {
            i++;
        }
        _local_p_head = (chunk_header_t*)_local_p_head->ch_ptr;
    } while (_local_p_head);
    printf("Free blocks: %d\n", i);
}
