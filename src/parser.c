#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "list.h"
#include "utils.h"
#include "parser.h"
#include "scan.h"

const char* IsMatch(const char* string, const char* dir)
{
    const char* last_slash = strrchr(string, '/');
    if (!last_slash) return NULL;

    const char* name = last_slash + 1;
    if (strcmp(name, dir) == 0)
        return string;
    else
        return NULL;
}

static void FilterHistoryEntries(FILE* f, ArrayList* list, ArrayList* config_f, const char* path, int check_config)
{
    char buffer[256];
    while (fgets(buffer, sizeof(buffer), f))
    {
        Entry result;
        buffer[strcspn(buffer, "\n")] = '\0';
        char tmp[256];
        if(sscanf(buffer, "%255s %d %ld", tmp, &result.rank, &result.last_acces) != 3) continue;
        if(IsMatch(tmp, path) && (!check_config || Config_result(config_f, tmp)))
        {
            result.path = strdup(tmp);
            if(!result.path)
            {
                perror("strdup");
                continue;
            }
            Arraylist_push(list, result);
        }
    }
}

ArrayList* parse_history_file(const char* filename, const char* path, const char* config)
{
    ArrayList* list = Arraylist_init(20);
    FILE* f = fopen(filename, "r");

    if(!f)return NULL;
    ArrayList* config_f = Scan_config(config);
    if(!config_f)
    {
        fclose(f);
        return NULL;
    }
    parse_history_file_pass(f,list,config_f,path,1);

    if(list->length == 0)
    {
        rewind(f);
        parse_history_file_pass(f,list,config_f,path,0);
    }
    fclose(f);
    qsort(list->entries, list->length, sizeof(Entry), Entry_Compare);
    return  list;
}

int ParseConfigAndPrintMatches(const char* config_visit, const char* visit_path,const char* history_path,const char* arg)
{
    ArrayList* list = parse_history_file(visit_path, arg, config_visit);
    if(list && list->length == 0)
    {
        ArrayList_Free(list);
        list = parse_history_file(history_path,arg, config_visit);
    }
    if(!list || list->length == 0)
    {
        if(list) ArrayList_Free(list);
        fprintf(stderr, "%sNothing found for%s: %s\n", RED, RESET,arg);
        return 1;
    }
    if(list->length == 1)
    {
        Entry result = ArrayList_GetIndex(list, 0);
        printf("%s\n",result.path);
    }
    else
    {
        Print_out(list, visit_path);
    }
    ArrayList_Free(list);
    return 0;
}
