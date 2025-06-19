#ifndef LIST_H
#define LIST_H

#include"entry.h"

typedef struct ArrayList
{ 
    Entry* entryNode;
    size_t length;
    size_t capacity;
    
} ArrayList;

ArrayList* Arraylist_init(size_t initial_capacity);
void Arraylist_push(ArrayList* list, Entry entry);
void Arraylist_free(ArrayList* list);
void Arraylist_printf(ArrayList* list);
Entry Arraylist_getIndex(ArrayList* list, int index);

#endif