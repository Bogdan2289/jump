cmake_minimum_required(VERSION 3.10)
project(jump C)

# Указываем стандарт
set(CMAKE_C_STANDARD 11)
set(CMAKE_BUILD_TYPE Debug)

# Добавляем include-папку
include_directories(include)

# Добавляем исходные файлы
set(SOURCES
    src/main.c
    src/scan.c
    src/parser.c
    src/list.c
    src/utils.c
)

# Собираем исполняемый файл
add_executable(jump ${SOURCES})