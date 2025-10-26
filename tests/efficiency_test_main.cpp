#include "include/tests.hpp"

int main()
{
    auto ef_Belady_test_runner = TestRunner<EfBeladyCache>();
    //auto Belady_test_runner = TestRunner<BeladyCache>();
    //auto LFU_test_runner = TestRunner<LFUCache>();

    ef_Belady_test_runner.run_big_test();
    //Belady_test_runner.run_big_test();
    //LFU_test_runner.run_big_test();
    
    return 0;
}