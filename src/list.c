#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "parser.h"
#include "utils.h"
#include"entry.h"

ArrayList* Arraylist_init(size_t initial_capacity)
{
    ArrayList* new_list = malloc(sizeof(ArrayList));
    if(!new_list) return NULL;

    new_list->entryNode = malloc(initial_capacity * sizeof(Entry));
    if(!new_list->entryNode)
    {
        free(new_list);
        return NULL;
    }
    new_list->capacity = initial_capacity;
    new_list->length = 0;
    return new_list;
}

void Arraylist_push(ArrayList* list, Entry entry)
{
    if(list->length >= list->capacity)
    {
        size_t new_capacity = 2 * list->capacity;   
        Entry* new_entries = realloc(list->entryNode, new_capacity * sizeof(Entry));
         if (!new_entries) 
         {
            perror("realloc failed in arraylist_push");
            exit(EXIT_FAILURE); 
        }
        list->entryNode = new_entries;
        list->capacity = new_capacity;
    }
    list->entryNode[list->length].path = strdup(entry.path);
    list->entryNode[list->length].rank = entry.rank;
    list->entryNode[list->length].last_acces = entry.last_acces;

    list->length++;
}

void Arraylist_free(ArrayList* list)
{
    if(!list) return ;
    for (size_t i = 0; i < list->length; i++)
    {
        free(list->entryNode[i].path);
    }
    free(list->entryNode);
    free(list);

}

void Arraylist_printf(ArrayList* list)
{
    Print_line();
    for (size_t i = 0; i < list->length; i++)
    {
        Entry* EntryNode = &list->entryNode[i];
        char time_buf[32];
        struct tm* tm_info = localtime(&EntryNode->last_acces);
        strftime(time_buf, sizeof(time_buf), "%Y-%m-%d %H:%M", tm_info);
        if(strcmp(time_buf, "1970-01-01 03:00") == 0)
        {
            fprintf(stderr,"[%s%zu%s] %s%-100s%s %-10d %s%s\n\n", YELLOW, i, RESET, YELLOW, EntryNode->path ? EntryNode->path:"NULL" ,RED, EntryNode->rank, "never", RESET);
        }
        else
        {
            fprintf(stderr,"[%s%zu%s] %s%-100s%s %-10d %s%s\n\n", YELLOW, i, RESET, BLUE, EntryNode->path ? EntryNode->path:"NULL" ,RED, EntryNode->rank, time_buf, RESET);
        }
    }
    Print_line();
          
}
Entry Arraylist_getIndex(ArrayList* list, int index)
{
     if (!list || !list->entryNode || index < 0 || index >= (int)list->length)
        perror("Index");

    return list->entryNode[index];
}
