#include <sys/ioctl.h>
#include <stdio.h>
#include <unistd.h>
#include <ncurses.h>
#include "parser.h"
#include "utils.h"
#include "scan.h"
#include "ncurses_menu.h"


int Entry_Compare(const void* a, const void* b)
{
    const Entry* e1 = (const Entry*)a;
    const Entry* e2 = (const Entry*)b;

    if (e1->rank != e2->rank)
        return e2->rank - e1->rank; 

    if (e1->last_acces!= e2->last_acces)
        return (e2->last_acces> e1->last_acces) ? 1 : -1;

    return 0; 
}

int Get_terminal_width()
{
    struct winsize w;
     
    if (ioctl(STDERR_FILENO, TIOCGWINSZ, &w) == -1) 
    {
        return 80; 
    }

    return w.ws_col;
}

void Ncurses_Print_Line(int y) {
    int width, c;
    getmaxyx(stdscr,c , width);
    attron(COLOR_PAIR(1));
    mvaddch(y, 0, '<');
    for (int i = 1; i < width - 1; i++) {
        addch('-');
    }
    addch('>');
    attroff(COLOR_PAIR(1));
}

void Print_out(ArrayList* list, const char* visit_path)
{
    Entry* dir = InteractiveMenu(list->entries, list->length);
    printf("%s\n",dir->path);
    Update_visit(dir->path, time(NULL),visit_path);
    AddNewVisitsToFile(list, visit_path);
}