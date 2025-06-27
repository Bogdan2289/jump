# tests/CMakeLists.txt

include_directories(${PROJECT_SOURCE_DIR}/include)
include_directories(${SQLITE3_INCLUDE_DIRS})
include_directories(${CUNIT_INCLUDE_DIRS})
include_directories(${NCURSES_INCLUDE_DIRS})


set(
    TEST_FILES
    test_list.c
    test_parser.c
    test_scan.c 
    test_utils.c
    test_main.c
    test_ncurses.c
)

add_executable(jump_tests ${TEST_FILES})
target_link_libraries(
    jump_tests
    PRIVATE jump_core
    cunit
    ${SQLITE3_LIBRARIES}
    ${CUNIT_LIBRARIES}
    ${NCURSES_LIBRARIES}
)

