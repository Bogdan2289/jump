# cmake_minimum_required(VERSION 3.10)
# project(jump C)


# set(CMAKE_C_STANDARD 11)
# set(CMAKE_BUILD_TYPE Debug)


# include_directories(include)

# set(SOURCES
#     src/main.c
#     src/core.c
#     src/scan.c
#     src/parser.c
#     src/list.c
#     src/utils.c
# )

# add_executable(jump ${SOURCES})
cmake_minimum_required(VERSION 3.10)
project(jump C)

set(CMAKE_C_STANDARD 99)
include_directories(include)

find_package(PkgConfig REQUIRED)

#CUnit
pkg_check_modules(CUNIT REQUIRED cunit)
include_directories(${CUNIT_INCLUDE_DIRS})
link_directories(${CUNIT_LIBRARY_DIRS})

#SQLite3
pkg_check_modules(SQLITE3 REQUIRED sqlite3)
include_directories(${SQLITE3_INCLUDE_DIRS})
link_directories(${SQLITE3_LIBRARY_DIRS})
#NCURSES
pkg_check_modules(NCURSES REQUIRED ncurses)
include_directories(${NCURSES_INCLUDE_DIRS})
link_directories(${NCURSES_LIBRARY_DIRS})

add_subdirectory(src)
add_subdirectory(tests)

# target_link_libraries(jump_core ${CUNIT_LIBRARIES} ${SQLITE3_LIBRARIES} ${NCURSES_LIBRARIES})
