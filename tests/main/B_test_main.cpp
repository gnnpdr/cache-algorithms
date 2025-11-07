#include "../tests/include/test.hpp"

using BeladyCacheInt = BeladyCache<int, int>;

int main()
{
    auto test_runner = TestRunner<BeladyCacheInt>();
    test_runner.run_tests();
    
    return 0;
}