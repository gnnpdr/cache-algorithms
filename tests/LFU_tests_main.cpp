#include "../include/LFU.hpp"
#include "include/tests.hpp"

int main()
{
    auto test_runner = TestRunner<LFUCache>();
    test_runner.run_tests();
    
    return 0;
}