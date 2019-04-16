cmake_minimum_required(VERSION 3.4)

project(palloc)

cmake_policy(SET CMP0065 NEW)

add_library(libpalloc STATIC palloc_heap.c)
set_property(TARGET libpalloc PROPERTY C_STANDARD 99)

if(${POOL})
    add_definitions(-DPOOL_SIZE=${POOL})
endif()

if(${SIZE})
    add_definitions(-DBLOCK_SIZE=${SIZE})
endif()
