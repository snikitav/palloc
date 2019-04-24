cmake_minimum_required(VERSION 3.4)

project(palloc)

cmake_policy(SET CMP0065 NEW)

add_library(palloc STATIC palloc_heap.c)
set_property(TARGET palloc PROPERTY C_STANDARD 99)

if(DEFINED POOL)
    if(NOT (${POOL} MATCHES "^[1-9]+$"))
        message(SEND_ERROR "Pool size must be a positive number")
    endif()
    add_definitions(-DPOOL_SIZE=${POOL})
endif()

if(DEFINED SIZE)
    if(NOT (SIZE MATCHES "^[1-9]+$"))
        message(SEND_ERROR "Block size must be a positive number")
    endif()
    add_definitions(-DBLOCK_SIZE=${SIZE})
endif()
