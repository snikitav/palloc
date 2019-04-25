cmake_minimum_required(VERSION 3.4)

project(palloc_test)

cmake_policy(SET CMP0065 NEW)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/..)

if(${POOL})
    add_definitions(-DPOOL_SIZE=${POOL})
endif()

if(${SIZE})
    add_definitions(-DBLOCK_SIZE=${SIZE})
endif()

add_library(palloc STATIC ../palloc_heap.c)
add_executable(palloc_test test.c)
set_property(TARGET palloc palloc_test PROPERTY C_STANDARD 99)

target_link_libraries(palloc_test palloc)

