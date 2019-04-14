cmake_minimum_required(VERSION 3.1)
project(PAlloc)

add_executable(PAlloc palloc_heap.c
                      main.c)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=c99 -pedantic -O3")

set(DEFAULT_ARCH "ARM")

if(DEFINED TARGET AND "${TARGET}" MATCHES "${DEFAULT_ARCH}")
    # TODO: . ensure that arm toolchain is installed
    #       . ensure that rtos does not need syscalls

    set(CMAKE_SYSTEM_PROCESSOR arm)

    set(CMAKE_CROSSCOMPILING 1)
    set(CMAKE_C_COMPILER arm-none-eabi-gcc)

    # known -rdynamic option bug for arm-none-eabi-gcc
    string(REPLACE "-rdynamic" "" CMAKE_SHARED_LIBRARY_LINK_C_FLAGS "${CMAKE_SHARED_LIBRARY_LINK_C_FLAGS}")
    # disable syscalls
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} --specs=nosys.specs")

    add_definitions(-DPALLOC_TARGET=ARM)

endif()

if(${POOL})
    add_definitions(-DPOOL_SIZE=${POOL})
endif()

if(${SIZE})
    add_definitions(-DBLOCK_SIZE=${SIZE})
endif()
