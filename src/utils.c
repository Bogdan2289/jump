#include<sys/ioctl.h>
#include<stdio.h>
#include<unistd.h>
#include"parser.h"
#include"utils.h"
#include"scan.h"


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

int Get_terminal_with()
{
    struct winsize w;
     
    if (ioctl(STDERR_FILENO, TIOCGWINSZ, &w) == -1) 
    {
        return 80; 
    }

    return w.ws_col;
}

void Print_line()
{
    fprintf(stderr,"%s\n", GREEN);
    int with = Get_terminal_with();
    fputc('<', stderr);
    for (size_t i = 0; i < with - 2; i++)
    {
        fputc('-', stderr);
    }
       fputc('>', stderr);
       fputc('\n', stderr);
       fprintf(stderr,"\033[0m\n");
}
void Print_out(ArrayList* list, const char visit_path[])
{

    Arraylist_printf(list);
    int index;
    scanf("%d",&index);
    Entry dir =  Arraylist_getIndex(list, index);
    printf("%s\n", dir.path);
    Update_visit(dir.path, time(NULL),visit_path);
    Add_visit(list, visit_path);
    Arraylist_free(list);
}