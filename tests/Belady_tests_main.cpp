#include "../include/Belady.hpp"
#include "include/tests.hpp"

int main()
{
    TestRunner Belady_test_runner(Belady_tests);
    
    Belady_test_runner.full_test();
    
    return 0;
}