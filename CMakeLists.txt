cmake_minimum_required(VERSION 3.4)

cmake_policy(SET CMP0065 NEW)

project(palloc)

set(PALLOC_OUTPUT_DIR ${CMAKE_CURRENT_BINARY_DIR}/out CACHE PATH "Output location")

set(POOL_SIZE 256 CACHE STRING "Pool size in blocks")
set(BLOCK_SIZE 8 CACHE STRING "Block size in bytes")

if(NOT (${POOL_SIZE} MATCHES "^[1-9]+[0-9]*$"))
    message(SEND_ERROR "Pool size must be a positive number")
endif()
add_definitions(-DPOOL_SIZE=${POOL_SIZE})

if(NOT (${BLOCK_SIZE} MATCHES "^[1-9]+[0-9]*$"))
    message(SEND_ERROR "Block size must be a positive number")
endif()
add_definitions(-DBLOCK_SIZE=${BLOCK_SIZE})

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/src)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/src/test)
