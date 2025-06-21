#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "core.h"
#include "utils.h"
#include "scan.h"
#include "parser.h"

int Core_Run(int argc, char** argv)
{
     if (argc < 2) 
    {
        fprintf(stderr, "%sUsage: %s [--update|search_term]%s\n", RED, argv[0], RESET);
        return 1;
    }

    const char* arg = argv[1];
    const char* home = getenv("HOME");
    if (!home) 
    {
        fprintf(stderr, "%sHOME environment variable not set%s\n", RED, RESET);
        return 1;
    }

    char history[512];
    snprintf(history, sizeof(history), "%s/Desktop/Project/jump/config/.jump_history", home);

    char visit_path[512];
    snprintf(visit_path, sizeof(visit_path), "%s/Desktop/Project/jump/config/.jump_visit" ,home);

    char config_visit[512];
    snprintf(config_visit,sizeof(config_visit),"%s/Desktop/Project/jump/config.jump.conf",home);
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
        return ParseConfigAndPrintMatches(config_visit,visit_path,history,arg);
    }
}