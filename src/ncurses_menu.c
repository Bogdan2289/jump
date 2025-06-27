
#include <string.h>
#include <ncurses.h>
#include "entry.h"
#include "ncurses_menu.h"
#include "utils.h"


Entry* InteractiveMenu(Entry *options, size_t count)
{
    FILE* out = stderr;  
    FILE* saved_stdout = stdout;
    stdout = out;

    initscr();              
    start_color();
    use_default_colors();
    init_pair(1, COLOR_GREEN, -1);

    init_pair(2, COLOR_RED, -1);   
    init_pair(3, COLOR_BLUE, -1);
    init_pair(4, COLOR_YELLOW, -1); 

    noecho();               
    curs_set(FALSE);        
    keypad(stdscr, TRUE);   

    int choice = 0;

    while (1)
    {
        clear();

        int height, width;
        getmaxyx(stdscr, height, width);

        int visible_count = height - 2; 
        int offset = 0;

        if (choice >= visible_count) 
        {
            offset = choice - visible_count + 1;
        }

        Ncurses_Print_Line(0);

        for (int i = 0; i < visible_count && (i + offset) < count; i++) 
        {
            int idx = i + offset;

            if (idx == choice) 
            {
                attron(A_REVERSE); 
            } 
            else 
            {
                attroff(A_REVERSE);
            }

            if (options[idx].rank == 0 && options[idx].last_acces == 0) 
            {
                attron(COLOR_PAIR(2)); 
                mvprintw(i + 1, 0, "[%d]", idx);
                attroff(COLOR_PAIR(2));

                attron(COLOR_PAIR(4)); 
                printw(" %s", options[idx].path);
                attroff(COLOR_PAIR(4));

                attron(COLOR_PAIR(2)); 
                printw(" %d %ld", options[idx].rank, options[idx].last_acces);
                attroff(COLOR_PAIR(2));
            } 
            else 
            {
                attron(COLOR_PAIR(2)); 
                mvprintw(i + 1, 0, "[%d]", idx);
                attroff(COLOR_PAIR(2));

                attron(COLOR_PAIR(3));
                printw(" %s", options[idx].path);
                attroff(COLOR_PAIR(3));

                attron(COLOR_PAIR(2)) ;
                printw(" %d %ld", options[idx].rank, options[idx].last_acces);
                attroff(COLOR_PAIR(2));
            }

            if (idx == choice) 
            {
                attroff(A_REVERSE);
            }
        }


        Ncurses_Print_Line(height - 1);

        refresh();

        int ch = getch();
        switch (ch)
        {
            case KEY_UP:
                choice = (choice - 1 + count) % count;
                break;
            case KEY_DOWN:
                choice = (choice + 1) % count;
                break;
            case '\n':
                endwin();
                stdout = saved_stdout;
                return &options[choice];
        }
    }
}

