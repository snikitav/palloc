cmake_minimum_required(VERSION 3.4)

project(palloc)

cmake_policy(SET CMP0065 NEW)

add_executable(palloc palloc_heap.c
                      main.c)
set_property(TARGET palloc PROPERTY C_STANDARD 99)

if(${POOL})
    add_definitions(-DPOOL_SIZE=${POOL})
endif()

if(${SIZE})
    add_definitions(-DBLOCK_SIZE=${SIZE})
endif()
