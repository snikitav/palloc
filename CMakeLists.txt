cmake_minimum_required(VERSION 3.1)
project(PAlloc)

add_executable(PAlloc palloc_heap.c
                      main.c)

if(${CMAKE_BUILD_TYPE} STREQUAL Debug)
add_definitions(-DDEBUG)
endif()

if(${POOL})
add_definitions(-DPOOL_SIZE=${POOL})
endif()

if(${SIZE})
add_definitions(-DBLOCK_SIZE=${SIZE})
endif()
