#include "../tests/include/tests.hpp"

int main()
{
    auto test_runner = TestRunner<EfBeladyCache>();
    test_runner.run_tests();
    
    return 0;
}