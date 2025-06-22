
#include <CUnit/CUnit.h>
#include <CUnit/Basic.h>
#include "utils.h"

void test_Entry_Compare()
{
    Entry a = { .rank = 5, .last_acces = 1000 };
    Entry b = { .rank = 3, .last_acces = 2000 };
    CU_ASSERT_TRUE(Entry_Compare(&a, &b) < 0);  // a > b по rank

    Entry c = { .rank = 5, .last_acces = 3000 };
    Entry d = { .rank = 5, .last_acces = 1000 };
    CU_ASSERT_TRUE(Entry_Compare(&c, &d) < 0);  // c > d по времени

    Entry e = { .rank = 2, .last_acces = 1000 };
    Entry f = { .rank = 2, .last_acces = 1000 };
    CU_ASSERT_EQUAL(Entry_Compare(&e, &f), 0);  // одинаковые
}


void Regist_Test_Utils()
{
    CU_pSuite suite = CU_add_suite("UtilsSuite", 0, 0);
    if (!suite) return;

    CU_add_test(suite, "Entry_Compare", test_Entry_Compare);
}