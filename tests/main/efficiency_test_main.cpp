#include "../tests/include/tests.hpp"

int main()
{
    std::cout << "ef_belady" << std::endl;

    auto ef_Belady_test_runner = TestRunner<EfBeladyCache>();
    ef_Belady_test_runner.run_big_test();

    std::cout << "belady" << std::endl;

    auto Belady_test_runner = TestRunner<BeladyCache>();
    Belady_test_runner.run_big_test();

    std::cout << "lfu" << std::endl;

    auto LFU_test_runner = TestRunner<LFUCache>();
    LFU_test_runner.run_big_test();
    
    return 0;
}