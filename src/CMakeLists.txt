project(palloc)

add_library(palloc STATIC palloc_heap.c)

set_target_properties(palloc PROPERTIES
                      ARCHIVE_OUTPUT_DIRECTORY ${PALLOC_OUTPUT_DIR}
                      C_STANDARD 99)

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
