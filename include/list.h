#ifndef LIST_H
#define LIST_H

#include "entry.h"

typedef struct ArrayList {
    Entry* entries;
    size_t length;
    size_t capacity;
} ArrayList;

ArrayList* ArrayList_Init(size_t initial_capacity);
void ArrayList_Push(ArrayList* list, Entry entry);
void ArrayList_Free(ArrayList* list);
void ArrayList_Print(ArrayList* list);
Entry  ArrayList_GetIndex(ArrayList* list, int index);

#endif
