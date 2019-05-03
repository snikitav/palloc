cmake_minimum_required(VERSION 3.4)

cmake_policy(SET CMP0065 NEW)

project(palloc_root)

set(LIBPALLOC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src CACHE PATH "Path to libpalloc sources")
set(PALLOC_TEST_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src/test CACHE PATH "Path to libpalloc test sources")
set(PALLOC_OUTPUT_DIR ${CMAKE_CURRENT_BINARY_DIR}/out CACHE PATH "Output location")

add_subdirectory(${PALLOC_TEST_DIR})
add_subdirectory(${LIBPALLOC_DIR})
