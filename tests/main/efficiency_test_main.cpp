#include "../tests/include/tests.hpp"

int main()
{
    std::cout << "Belady:" << std::endl;
    auto Belady_test_runner = TestRunner<BeladyCache>();
    Belady_test_runner.run_big_test();

    std::cout << "LFU:" << std::endl;
    auto LFU_test_runner = TestRunner<LFUCache>();
    LFU_test_runner.run_big_test();
    
    return 0;
}