#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "parser.h"
#include "utils.h"
#include "entry.h"

ArrayList* ArrayList_Init(size_t initial_capacity)
{
    ArrayList* new_list = malloc(sizeof(ArrayList));
    if(!new_list) return NULL;

    new_list->entries = malloc(initial_capacity * sizeof(Entry));
    if(!new_list->entries)
    {
        free(new_list);
        return NULL;
    }
    new_list->capacity = initial_capacity;
    new_list->length = 0;
    return new_list;
}

void ArrayList_Push(ArrayList* list, Entry entry)
{
    if(list->length >= list->capacity)
    {
        size_t new_capacity = 2 * list->capacity;   
        Entry* new_entries = realloc(list->entries, new_capacity * sizeof(Entry));
         if (!new_entries) 
         {
            perror("realloc failed in arraylist_push");
            exit(EXIT_FAILURE); 
        }
        list->entries = new_entries;
        list->capacity = new_capacity;
    }
    list->entries[list->length].path = strdup(entry.path ? entry.path: "");
    if(!list->entries[list->length].path)
    {
        perror("strdup fail");
        exit(EXIT_FAILURE);
    }
    list->entries[list->length].rank = entry.rank;
    list->entries[list->length].last_acces = entry.last_acces;

    list->length++;
}

void ArrayList_Free(ArrayList* list)
{
    if(!list) return ;
    for (size_t i = 0; i < list->length; i++)
    {
        free(list->entries[i].path);
    }
    free(list->entries);
    free(list);

}

void ArrayList_Print(ArrayList* list)
{
    if (!list || !list->entries)
    {
        fprintf(stderr, "%sArrayList is NULL%s\n", RED, RESET);
        return;
    }
    
    // Print_Line();
    for (size_t i = 0; i < list->length; i++)
    {
        Entry* entry = &list->entries[i];
        char time_buf[32];
        struct tm* tm_info = localtime(&entry->last_acces);
        if (!tm_info) 
        {
            strcpy(time_buf, "invalid");
        }
        else
        {
            strftime(time_buf, sizeof(time_buf), "%Y-%m-%d %H:%M", tm_info);
        }
        if(entry->last_acces == 0)
        {
            fprintf(stderr,"[%s%zu%s] %s%-100s%s %-10d %s%s\n\n", YELLOW, i, RESET, YELLOW, entry->path ? entry->path:"NULL" ,RED, entry->rank, "never", RESET);
        }
        else
        {
            fprintf(stderr,"[%s%zu%s] %s%-100s%s %-10d %s%s\n\n", YELLOW, i, RESET, BLUE, entry->path ? entry->path:"NULL" ,RED, entry->rank, time_buf, RESET);
        }
    }
    // Print_Line();
          
}

Entry* ArrayList_GetIndex(ArrayList* list, int index)
{
     if (!list || !list->entries || index < 0 || index >= (int)list->length)
     {
         fprintf(stderr, "ArrayList_GetIndex: invalid index %d\n", index);
         return NULL;
     }

    return &list->entries[index];
}
