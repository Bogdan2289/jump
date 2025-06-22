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

add_subdirectory(src)
add_subdirectory(tests)
