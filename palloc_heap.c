#include "palloc_heap.h"

// free node
static chunk_header_t* _p_head = NULL;
// allocatable data
static char  _pool[(POOL_SIZE * BLOCK_SIZE) + (sizeof(chunk_header_t) * CHUNKS_NUM)];
// full chunks number
static size_t chunks_num = CHUNKS_NUM;
size_t block_size = BLOCK_SIZE;
size_t l_ch_size = LAST_CHUNK_SIZE;

int palloc_init()
{
    full_chunk_t* chunk = (full_chunk_t *) _pool;
    _p_head = &chunk->header;

    // build in-place linked list of available chunks
    int i, j, chunk_size;
    for(i = 0; i <= CHUNKS_NUM; i++, chunk++)
    {
        chunk->header.ch_ptr = (header_ptr_t)(chunk + 1);
        chunk->header.ch_head = 0;
        chunk_size = (i == CHUNKS_NUM) ? LAST_CHUNK_SIZE : CHUNK_SIZE;
        for(j = 0; j < chunk_size; j++)
        {
            char* data = chunk->data;
            *(data + BLOCK_SIZE * j) = j + 1; // possible error, test it!
        }

        chunk->header.n_free_blks = chunk_size; // calculate last chunk size here
    }

    if (CHUNKS_NUM > 1)
    {
        // last chunk header points to null
        chunk->header.ch_ptr = NULL;
    }
    else
    {
        _p_head->ch_ptr = (header_ptr_t)(&chunk->header.ch_ptr);
    }

    return 0;
}

void* palloc_allocate()
{
    if(_p_head == NULL)
    {
        // no space left in a pool
        return NULL;
    }

    full_chunk_t* chunk = (full_chunk_t*) _p_head;
    char* block_ptr = chunk->data;

    block_ptr = (block_ptr + (BLOCK_SIZE * chunk->header.ch_head));
    chunk->header.ch_head = *block_ptr;
    if(--chunk->header.n_free_blks == 0)
    {
        chunk->header.ch_ptr = NULL;
        _p_head = (chunk_header_t*)_p_head->ch_ptr;
    }

    return (void*) block_ptr;
}

void palloc_free(void* ptr)
{
    // TODO: check if pointer is allocated in the pool
    if(ptr == NULL)
    {
        return;
    }

    // first, calculate block num for a given ponter
    uintptr_t block_uptr = (uintptr_t) ptr;
    uintptr_t pool_uptr = (uintptr_t)_pool;
    uintptr_t block_num = ((block_uptr - pool_uptr) - sizeof(chunk_header_t)) / BLOCK_SIZE;
    // second, find out pointer to corresponding chunk
    full_chunk_t* chunk = (full_chunk_t*)(block_uptr - (block_num * BLOCK_SIZE) - sizeof(chunk_header_t));

    char* data = chunk->data;
    *(data + BLOCK_SIZE * block_num) = chunk->header.ch_head;
    chunk->header.ch_head = block_num;
    if (chunk->header.n_free_blks++ == 0)
    {
        chunk_header_t* tmp_ptr = (chunk_header_t*)chunk;
        if(_p_head)
        {
            chunk = (full_chunk_t*)_p_head->ch_ptr;
        }
        _p_head = tmp_ptr;
    }
}

// Debug info, to be deleted
void print_sizes()
{
    printf("Block size: %d\n", BLOCK_SIZE);
    printf("Pool size: %d\n", POOL_SIZE);

    int i = 0;
    do
    {
        int j;
        for(j = 0; j < _p_head->n_free_blks; j++)
        {
            i++;
        }
        _p_head = (chunk_header_t*)_p_head->ch_ptr;
    } while (_p_head);
    printf("Free chunks: %d\n", i);
}
