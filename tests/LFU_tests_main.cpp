#include "../include/LFU.hpp"
#include "include/tests.hpp"

int main()
{
    TestRunner LFU_test_runner(LFU_tests);
    
    LFU_test_runner.full_test();
    
    return 0;
}