#ifndef PARSER_H
#define PARSER_H

#include<time.h>
#include"list.h"

const char* IsMatch(const char* string, const char* dir);
ArrayList* parse_history_file(const char* filename, const char* path, const char* config_path);
int ParseConfigAndPrintMatches(const char* config_visit, const char* visit_path,const char* history_path,const char* arg);

#endif