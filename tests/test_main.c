
#include <CUnit/CUnit.h>
#include <CUnit/Basic.h>

void Regist_Test_List();
void Regist_Test_Parser();
void Regist_Test_Scan();
void Regist_Test_Utils();
void Regist_Test_Core();


int main() {
    CU_initialize_registry();
    Regist_Test_List();
    Regist_Test_Scan();
    Regist_Test_Parser(); 
    CU_basic_run_tests();
    CU_cleanup_registry();
    return 0;
}
