#include "../include/tests.hpp"

TestRunner::TestRunner(std::vector<TestData> tests) : tests(tests) {}

void TestRunner::full_test()
{
    for (TestData test : tests)
        single_test(test);

    print_results();
}

void TestRunner::single_test(TestData test)
{
    total_test_amt++;

    size_t matches = 0;
    size_t el_amt = test.el_amt;
    std::vector<int> reqs = test.reqs;
    size_t capacity = test.capacity;
    LFUCache cache(capacity, el_amt, reqs);

    for (int i = 0; i < test.el_amt; i++)
    {
        int k = reqs[i];
        matches = cache.cache_push(k);
    }
    if (matches != test.match_amt)
        std::cout << "test " << total_test_amt << " failed. " << "Expected " << test.match_amt << " Received " << matches << std::endl;
    else
    {
        passed_test_amt++;
        std::cout << "test " << total_test_amt << " is good" << std::endl;
    }
}

void TestRunner::print_results()
{
    if (total_test_amt != passed_test_amt)
    {
        std::cout << passed_test_amt << " out of " << total_test_amt << " tests passed\nDO SOMETHING WITH IT" << std::endl;
    }
    else
        std::cout << "ALL TESTS PASSED CONGRATULATIONS!" << std::endl;
}