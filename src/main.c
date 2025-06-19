#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"scan.h"
#include"parser.h"
#include"list.h"
#include"utils.h"

int main(int argc, char** argv)
{
    if (argc < 2) 
    {
        return 1;
    }

    const char* arg = argv[1];
    const char* home = getenv("HOME");

    char history[512];
    snprintf(history, sizeof(history), "%s/Jump/build/.jump_history", home);

    char visit_path[512];
    snprintf(visit_path, sizeof(visit_path), "%s/Jump/build/.jump_visit" ,home);

    char config_visit[512];
    snprintf(config_visit,sizeof(config_visit),"%s/.jump.conf",home);
    ArrayList* list;
    if (strcmp(arg, "--update") == 0) 
    {
        FILE* f = fopen(history, "w");
        if (!f) 
        {
            fprintf(stderr, "%sError creating history%s", RED, RESET);
            return 1;
        }

        scan_and_write_dirs("/", f);
        fclose(f);
        return 0;
    } 
    else 
    {
        Parser_config_file(config_visit,visit_path,history,arg);
        return 0;
    }

}
