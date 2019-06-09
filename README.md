# palloc

Simple and lightweight block pool allocator intended to be used in RTOS. It has fixed memory block size and fixed allocation and deallocation time.

Size of a pool and a block should be specified in compile time.

#### Memory organization:
Palloc memory blocks organized in chunks. Each chunk contains 255 blocks and 10 bytes of meta information. It was done so to reduce memory waste on a meta information.

#### How to build:
Clone the repo, then in repo folder:
 - mkdir build && cd build
 - cmake .. -DBLOCK_SIZE=32 -DPOOL_SIZE=128
 - make

`BLOCK_SIZE` is size of fixed memory block in bytes, and `POOL_SIZE` is size of fixed memory pool in blocks. If you don't specify them, default values are: 8 for `BLOCK_SIZE` and 256000 for `POOL_SIZE`

After compilation, you'll find `libpalloc.a` in `build/out` directory. Note, that by default palloc is built as a static library.

#### How to use:
Before any allocation, initialize allocator with `void palloc_init()` function

To get a block of data, use `void* palloc_allocate()` function

To release a block, use `void palloc_free(void* ptr)` function

#### Thread safety:
Currently, palloc has no out of the box thread safety support.

But it can be implemented on a client side. Before adding to your code include line:

`#include palloc_heap.h`

you can implement macro `PALLOC_LOCK()` and `PALLOC_UNLOCK()` to lock and unlock palloc allocate/free functions.

#### Known problems and workarounds:
- For `arm-none-eabi-gcc` compiler, set C flag `--specs=nosys.specs`
