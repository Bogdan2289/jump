#ifndef UTILS_H
#define UTILS_H

#include <sys/ioctl.h>
#include <stdio.h>
#include <unistd.h>
#include "list.h"

#define YELLOW "\033[1;33m"
#define GREEN "\033[1;32m"
#define RED "\033[1;31m"
#define BLUE "\033[1;34m"
#define RESET "\033[0m"

int Entry_Compare(const void* a, const void* b);
int Get_terminal_width();
void Print_Line();
void Print_out(ArrayList* list, const char* visit_path);

#endif