#ifndef ENTRY_H
#define ENTRY_H

#include<time.h>

typedef struct
{
    char* path;
    int rank;
    time_t last_acces;

}Entry;

#endif