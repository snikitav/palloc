project(palloc)

add_library(palloc STATIC palloc_heap.c)

set_target_properties(palloc PROPERTIES
                      ARCHIVE_OUTPUT_DIRECTORY ${PALLOC_OUTPUT_DIR}
                      C_STANDARD 99)
