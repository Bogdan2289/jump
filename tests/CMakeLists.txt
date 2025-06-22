# tests/CMakeLists.txt

include_directories(${PROJECT_SOURCE_DIR}/include)
include_directories(/usr/include/CUnit) 

set(TEST_FILES
    test_list.c
    test_parser.c
    test_scan.c 
    test_utils.c
    test_main.c
)

add_executable(jump_tests ${TEST_FILES})
target_link_libraries(jump_tests PRIVATE jump_core cunit)

