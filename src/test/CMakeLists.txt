add_executable(palloc_test test.c)

set_target_properties(palloc_test PROPERTIES
                      RUNTIME_OUTPUT_DIRECTORY ${PALLOC_OUTPUT_DIR}/test
                      C_STANDARD 99)

target_link_libraries(palloc_test palloc)
