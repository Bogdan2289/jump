set(SRC_FILES
    core.c
    utils.c
    scan.c
    parser.c
    list.c
    ncurses_menu.c
)

add_library(jump_core STATIC ${SRC_FILES})
add_executable(jump main.c)
target_link_libraries(jump jump_core ${SQLITE3_LIBRARIES} ${NCURSES_LIBRARIES})
