#include "Belady_tests.hpp"
#include "LFU_tests.hpp"

int main()
{
    std::cout << "Belady:" << std::endl;
    auto Belady_test_runner = BeladyTestRunner<int, int>();
    Belady_test_runner.run_big_test();

    std::cout << "LFU:" << std::endl;
    auto LFU_test_runner = LFUTestRunner<int, int>();
    LFU_test_runner.run_big_test();
    
    return 0;
}