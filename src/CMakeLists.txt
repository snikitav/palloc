add_library(palloc STATIC palloc_heap.c)

set_target_properties(palloc PROPERTIES
                      ARCHIVE_OUTPUT_DIRECTORY ${PALLOC_OUTPUT_DIR}
                      C_STANDARD 99)

target_include_directories(palloc PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
