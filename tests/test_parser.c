#include <CUnit/CUnit.h>
#include <CUnit/Basic.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "parser.h"
#include "list.h"

void test_IsMatch(void)
{
    CU_ASSERT_PTR_NULL(IsMatch("somepath/file.txt", "other"));
    CU_ASSERT_STRING_EQUAL(IsMatch("/home/user/xinit", "xinit"), "/home/user/xinit");
    CU_ASSERT_PTR_NULL(IsMatch("no_slash_in_path", "xinit"));
}

void test_parse_history_file(void)
{
    const char* filename = "test_history.txt";
    FILE* f = fopen(filename, "w");
    fprintf(f, "/home/user/xinit 10 1000000\n/home/user/other 5 500000\n");
    fclose(f);
  
    const char* configfile = "test_config.txt";
    f = fopen(configfile, "w");
    fprintf(f, "/home/user/xinit\n");
    fclose(f);

    ArrayList* list = parse_history_file(filename, "xinit", configfile);
    CU_ASSERT_PTR_NOT_NULL(list);
    CU_ASSERT(list->length > 0);

    if(list->length > 0)
    {
        CU_ASSERT_STRING_EQUAL(list->entries[0].path, "/home/user/xinit");
        CU_ASSERT(list->entries[0].rank == 10);
    }
    ArrayList_Free(list);

    remove(filename);
    remove(configfile);
}

void test_ParseConfigAndPrintMatches(void)
{
    const char* visit_path = "test_visit.txt";
    const char* history_path = "test_history.txt";
    const char* config_visit = "test_config.txt";

    FILE* f = fopen(visit_path, "w");
    fprintf(f, "/home/user/xinit 15 2000000\n");
    fclose(f);

    f = fopen(history_path, "w");
    fprintf(f, "/home/user/xinit 10 1000000\n/home/user/other 5 500000\n");
    fclose(f);

    f = fopen(config_visit, "w");
    fprintf(f, "/home/user/xinit\n");
    fclose(f);

    int ret = ParseConfigAndPrintMatches(config_visit, visit_path, history_path, "xinit");
    CU_ASSERT_EQUAL(ret, 0);

    ret = ParseConfigAndPrintMatches(config_visit, visit_path, history_path, "nonexistent");
    CU_ASSERT_EQUAL(ret, 1);

    remove(visit_path);
    remove(history_path);
    remove(config_visit);
}

void Regist_Test_Parser()
{
    CU_pSuite suite = CU_add_suite("ParserTestSuite", NULL, NULL);
    CU_add_test(suite, "test_IsMatch", test_IsMatch);
    CU_add_test(suite, "test_parse_history_file", test_parse_history_file);
    CU_add_test(suite, "test_ParseConfigAndPrintMatches", test_ParseConfigAndPrintMatches);
}
