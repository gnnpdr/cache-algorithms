#include "../tests/include/test.hpp"

int main()
{
    std::cout << "int key test..." << std::endl;
    auto test_runner_int = TestRunner<BeladyCache<int, int>>();
    test_runner_int.run_tests();
    std::cout << std::endl;

    std::cout << "double key test..." << std::endl;
    auto test_runner_double = TestRunner<BeladyCache<double, int>>();
    test_runner_double.run_tests();
    std::cout <<  std::endl;

    std::cout << "string key test..." << std::endl;
    auto test_runner_string = TestRunner<BeladyCache<std::string, int>>();
    test_runner_string.run_tests();
    std::cout <<  std::endl;
    
    return 0;
}