#ifndef SCAN_H
#define SCAN_H

#include<stdio.h>
#include"list.h"

void scan_and_write_dirs(const char *path, FILE*out);
void Update_visit(const char* target_path, time_t new_time, const char* visit_path);
void Add_visit(ArrayList* list, const char* visit);
int Path_exist(const char* filename, const char* path);
int Config_result(ArrayList* config_str ,const char tmp[]);
ArrayList* Scan_config(const char config[]);

#endif