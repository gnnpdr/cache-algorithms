#include "../tests/include/tests.hpp"

int main()
{
    auto ef_Belady_test_runner = TestRunner<EfBeladyCache>();
    ef_Belady_test_runner.run_big_test();

    auto Belady_test_runner = TestRunner<BeladyCache>();
    Belady_test_runner.run_big_test();

    auto LFU_test_runner = TestRunner<LFUCache>();
    LFU_test_runner.run_big_test();
    
    return 0;
}