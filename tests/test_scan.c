
#include <CUnit/CUnit.h>
#include <CUnit/Basic.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>
#include "scan.h"
#include "list.h"

void test_Path_exist(void)
{
    const char* file = "test_visits.txt";
    FILE* f = fopen(file, "w");
    fprintf(f, "/home/user/dir1 1 100\n");
    fclose(f);

    CU_ASSERT_TRUE(Path_exist(file, "/home/user/dir1"));
    CU_ASSERT_FALSE(Path_exist(file, "/home/user/dir2"));

    remove(file);
}

void test_Update_visit(void)
{
    const char* file = "test_visits.txt";
    FILE* f = fopen(file, "w");
    fprintf(f, "/home/user/dir1 1 100\n");
    fclose(f);

    Update_visit("/home/user/dir1", 200, file);
    Update_visit("/home/user/dir2", 300, file);

    f = fopen(file, "r");
    char line[256];
    int found_dir1 = 0, found_dir2 = 0;
    while (fgets(line, sizeof(line), f))
    {
        if (strstr(line, "/home/user/dir1") && strstr(line, "2"))
            found_dir1 = 1;
        if (strstr(line, "/home/user/dir2") && strstr(line, "1"))
            found_dir2 = 1;
    }
    fclose(f);
    CU_ASSERT_TRUE(found_dir1);
    CU_ASSERT_TRUE(found_dir2);

    remove(file);
}

void test_AddNewVisitsToFile(void)
{
    const char* file = "test_add.txt";
    FILE* f = fopen(file, "w");
    fprintf(f, "/known/path 0 0\n");
    fclose(f);

    ArrayList* list = ArrayList_Init(2);
    Entry e1 = { "/known/path", 0, 0 };
    Entry e2 = { "/new/path", 0, 0 };
    ArrayList_Push(list, e1);
    ArrayList_Push(list, e2);

    // fclose(f);
    AddNewVisitsToFile(list, file);

    f = fopen(file, "r");
    char line[256];
    int found = 0;
    while (fgets(line, sizeof(line), f))
    {

        line[strcspn(line, "\n")] = '\0';
        char path_only[256];
        if (sscanf(line, "%255s", path_only) == 1 && strcmp(path_only, "/new/path") == 0)
        {
            found = 1;
            break;
        }
    }
    fclose(f);
    CU_ASSERT_TRUE(found);

    ArrayList_Free(list);
    remove(file);
}


void test_Scan_config_and_Config_result(void)
{
    const char* config = "test_config.txt";
    FILE* f = fopen(config, "w");
    fprintf(f, "/match/path\n[comment]\n/other/path\n");
    fclose(f);

    ArrayList* conf = Scan_config(config);
    CU_ASSERT_PTR_NOT_NULL(conf);
    CU_ASSERT_EQUAL(conf->length, 2);
    CU_ASSERT_TRUE(Config_result(conf, "/match/path"));
    CU_ASSERT_FALSE(Config_result(conf, "/not/found"));

    ArrayList_Free(conf);
    remove(config);
}

void test_scan_and_write_dirs(void)
{
    mkdir("test_dir", 0755);
    mkdir("test_dir/subdir", 0755);

    FILE* f = fopen("scan_output.txt", "w");
    scan_and_write_dirs("test_dir", f);
    fclose(f);

    f = fopen("scan_output.txt", "r");
    char buffer[512];
    int found_subdir = 0;
    while (fgets(buffer, sizeof(buffer), f))
    {
        if (strstr(buffer, "subdir"))
            found_subdir = 1;
    }
    fclose(f);

    CU_ASSERT_TRUE(found_subdir);

    remove("scan_output.txt");
    rmdir("test_dir/subdir");
    rmdir("test_dir");
}

void Regist_Test_Scan()
{
    CU_initialize_registry();
    CU_pSuite suite = CU_add_suite("ScanSuite", 0, 0);

    CU_add_test(suite, "test_Path_exist", test_Path_exist);
    CU_add_test(suite, "test_Update_visit", test_Update_visit);
    CU_add_test(suite, "test_AddNewVisitsToFile", test_AddNewVisitsToFile);
    CU_add_test(suite, "test_Scan_config_and_Config_result", test_Scan_config_and_Config_result);
    CU_add_test(suite, "test_scan_and_write_dirs", test_scan_and_write_dirs);

}
