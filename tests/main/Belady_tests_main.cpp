#include "../include/Belady_tests.hpp"

int main()
{
    std::cout << "int key test..." << std::endl;
    auto test_runner_int = BeladyTestRunner<int, int>();
    test_runner_int.run_tests();
    std::cout << std::endl;

    std::cout << "double key test..." << std::endl;
    auto test_runner_double = BeladyTestRunner<double, int>();
    test_runner_double.run_tests();
    std::cout <<  std::endl;

    std::cout << "string key test..." << std::endl;
    auto test_runner_string = BeladyTestRunner<std::string, int>();
    test_runner_string.run_tests();
    
    return 0;
}