#include<stdio.h>
#include<string.h>
#include<dirent.h>
#include<time.h>
#include"scan.h"
#include"list.h"
#include"utils.h"

void scan_and_write_dirs(const char *path, FILE*out)
{
    DIR *dir = opendir(path);
    if(!dir) return;
    struct dirent *entry;

    while((entry = readdir(dir)) != NULL)
    {
         if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)continue;

        char full_path[4096];

        if(path[strlen(path) - 1 ] == '/')
        {
            snprintf(full_path, sizeof(full_path), "%s%s", path, entry->d_name);
        }
        else
        {
            snprintf(full_path, sizeof(full_path), "%s/%s", path, entry->d_name);
        }
        if (entry->d_type == DT_DIR) 
        {
            fprintf(out, "%s 0 0\n", full_path);
            scan_and_write_dirs(full_path, out);
        }
    }

    closedir(dir);
    
}

void Update_visit(const char* target_path, time_t new_time, const char* visit_path)
{
    char tmp_path[512];
    snprintf(tmp_path, sizeof(tmp_path), "%s_tmp", visit_path);

    FILE* in = fopen(visit_path, "r");
    FILE* out = fopen(tmp_path, "w");

    if (!in || !out) 
    {
        perror("File open");
        if (in) fclose(in);
        if (out) fclose(out);
        return;
    }

    char path[256];
    int count;
    long timeshift;
    char line[512];
    int was_found = 0;

    while (fgets(line, sizeof(line), in)) 
    {
        if (sscanf(line, "%255s %d %ld", path, &count, &timeshift) == 3) 
        {
            if (strcmp(path, target_path) == 0) 
            {
                fprintf(out, "%s %d %ld\n", path, count + 1, new_time);
                was_found = 1;
            } 
            else 
            {
                fputs(line, out);
            }
        } 
        else 
        {
            fputs(line, out);
        }
    }

    if (!was_found) 
    {
        fprintf(out, "%s %d %ld\n", target_path, 1, new_time);
    }

    fclose(in);
    fclose(out);

    if (remove(visit_path) != 0 || rename(tmp_path, visit_path) != 0) 
    {
        fprintf(stderr, "%sError replacing file%s", RED ,RESET);
    }
}

int Path_exist(const char* filename, const char* path)
{
    FILE* f = fopen(filename, "r");
    if (!f) return 0;

    char line[512], existing[256];
    while (fgets(line, sizeof(line), f)) 
    {
        if (sscanf(line, "%255s", existing) == 1) 
        {
            if (strcmp(existing, path) == 0) 
            {
                fclose(f);
                return 1;
            }
        }
    }

    fclose(f);
    return 0;
}

void Add_visit(ArrayList* list, const char* visit)
{
    FILE* f = fopen(visit, "a");
    for (size_t i = 0; i < list->length; i++)
    {
        const char* path = list->entryNode[i].path;
        if(!Path_exist(visit, path))
        {
            fprintf(f,"%s 0 0\n", path);
        }
    }

    
}

ArrayList* Scan_config(const char config[])
{
    FILE* config_f = fopen(config,"r");
    ArrayList* result = Arraylist_init(10);
    Entry EntryNode;
    char buffer[256];

    while (fgets(buffer, sizeof(buffer), config_f))
    {
        buffer[strcspn(buffer,"\n")] = '\0';
        if(buffer[0] != '[')
        {
            EntryNode.path = buffer;
            EntryNode.last_acces = 0;
            EntryNode.rank = 0;
            Arraylist_push(result, EntryNode);
        }
    }
    fclose(config_f);
    return result;
}

int Config_result(ArrayList* config_str ,const char tmp[])
{
    for (size_t i = 0; i < config_str->length; i++)
    {
        
        if(strcmp(tmp, config_str->entryNode[i].path) == 0)
        {
            return 1;
        }
    }
    return 0;
}