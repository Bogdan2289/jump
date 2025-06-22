#include <CUnit/CUnit.h>
#include <CUnit/Basic.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "list.h"

void test_ArrayList_Init()
{
    size_t capacity = 10;
    ArrayList* list = ArrayList_Init(capacity);
    CU_ASSERT_PTR_NOT_NULL(list);
    CU_ASSERT_EQUAL(list->length, 0);
    CU_ASSERT_EQUAL(list->capacity, capacity);
    ArrayList_Free(list);
}

void test_Array_List_Push()
{
    ArrayList* list = ArrayList_Init(2);

    Entry e1 = { .path = "test/path1", .rank = 1, .last_acces = 1000 };
    Entry e2 = { .path = "test/path2", .rank = 2, .last_acces = 2000 };
    Entry e3 = { .path = "test/path3", .rank = 3, .last_acces = 3000 };

    ArrayList_Push(list, e1);
    ArrayList_Push(list, e2);
    ArrayList_Push(list, e3);

    CU_ASSERT_EQUAL(list->length, 3);
    CU_ASSERT_TRUE(list->capacity >= 3);

    CU_ASSERT_STRING_EQUAL(list->entries[0].path, "test/path1");
    CU_ASSERT_EQUAL(list->entries[1].rank, 2);
    CU_ASSERT_EQUAL(list->entries[2].last_acces, 3000);

    ArrayList_Free(list);
}

void test_ArrayList_Free()
{
    ArrayList* list = ArrayList_Init(2);
    Entry e = { strdup("test/path"), 1, 100 };
    ArrayList_Push(list, e);
    free(e.path);

    CU_ASSERT_PTR_NOT_NULL(list);
    CU_ASSERT_PTR_NOT_NULL(list->entries[0].path);

    ArrayList_Free(list); 
}


void test_ArrayList_GetIndex(void)
{
    ArrayList* list = ArrayList_Init(2);
    CU_ASSERT_PTR_NOT_NULL(list);

    Entry e1 = { strdup("/home/test1"), 10, 1000 };
    Entry e2 = { strdup("/home/test2"), 20, 2000 };

    ArrayList_Push(list, e1);
    ArrayList_Push(list, e2);

    Entry* res1 = ArrayList_GetIndex(list, 0);
    CU_ASSERT_PTR_NOT_NULL(res1);
    CU_ASSERT_STRING_EQUAL(res1->path, "/home/test1");
    CU_ASSERT_EQUAL(res1->rank, 10);
    CU_ASSERT_EQUAL(res1->last_acces, 1000);

    Entry* res2 = ArrayList_GetIndex(list, 1);
    CU_ASSERT_PTR_NOT_NULL(res2);
    CU_ASSERT_STRING_EQUAL(res2->path, "/home/test2");
    CU_ASSERT_EQUAL(res2->rank, 20);
    CU_ASSERT_EQUAL(res2->last_acces, 2000);

    Entry* invalid = ArrayList_GetIndex(list, 10);
    CU_ASSERT_PTR_NULL(invalid);

    ArrayList_Free(list);
}

void Regist_Test_List()
{
    
    CU_pSuite suite = CU_add_suite("ArrayList_Test_Suite", NULL, NULL);

    CU_add_test(suite, "test_ArrayList_Init", test_ArrayList_Init);
    CU_add_test(suite, "test_ArrayList_Push", test_Array_List_Push);
    CU_add_test(suite, "test_ArrayList_Free", test_ArrayList_Free);
    CU_add_test(suite, "test_ArrayList_GetIndex", test_ArrayList_GetIndex);

    CU_basic_set_mode(CU_BRM_VERBOSE);
}
