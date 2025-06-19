#ifndef PARSER_H
#define PARSER_H

#include<time.h>
#include"list.h"

ArrayList* parse_history_file(const char* filename, const char* path, const char config[]);
// size_t count_lines_in_file(const char* filename);
const char* parser(const char* string, const char* dir);
int Parser_config_file(const char config_visit[], const char visit_path[],const char history_path[],const char* arg);

#endif