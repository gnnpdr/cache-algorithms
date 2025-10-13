#include "../include/tests.hpp"

void TestRunner::test(size_t res, size_t expected_res)
{
    total_test_amt++;
    if (res == expected_res)
        passed_test_amt++;
    else
    {
        std::cout << "test " << total_test_amt << " failed. " << "Expected " << expected_res << " Received " << res << std::endl;
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

void run_Belady_tests()
{
    std::cout << "RUN BELADY TESTS!" << std::endl;

    TestRunner runner;
    size_t matches = 0;

    size_t el_amt = 6;
    std::vector<int> reqs1 = {1, 2, 1, 2, 1, 2};
    BeladyCache cache1(2, reqs1);

    for (int i = 0; i < 2; i++)
    {
        int k = reqs1[i];
        matches = cache1.cache_push(k);
    }
    runner.test(matches, 0);

    for (int i = 2; i < el_amt; i++) 
    {
        int k = reqs1[i];
        matches = cache1.cache_push(k);
    }
    runner.test(matches, 4);

    matches = 0;
    el_amt = 10;
    std::vector<int> reqs2 = {1, 2, 3, 1, 2, 3, 4, 4, 4, 7};
    BeladyCache cache2(5, reqs2);
    for (int i = 0; i < el_amt; i++)
    {
        int k = reqs2[i];
        matches = cache2.cache_push(k);
    }
    runner.test(matches, 5);

    matches = 0;
    el_amt = 9;
    std::vector<int> reqs3 = {1, 2, 3, 7, 2, 5, 3, 5, 1};
    BeladyCache cache3(3, reqs3);
    for (int i = 0; i < el_amt; i++)
    {
        int k = reqs3[i];
        matches = cache3.cache_push(k);
    }
    runner.test(matches, 3);

    runner.print_results();
}

void run_LFU_tests()
{
    std::cout << "RUN LFU TESTS!" << std::endl;
    
    TestRunner runner;
    size_t matches = 0;

    size_t el_amt = 6;
    std::vector<int> reqs1 = {1, 2, 1, 2, 1, 2};
    LFUCache cache1(2, reqs1);

    for (int i = 0; i < 2; i++)
    {
        int k = reqs1[i];
        matches = cache1.cache_push(k);
    }
    runner.test(matches, 0);

    for (int i = 2; i < el_amt; i++)
    {
        int k = reqs1[i];
        matches = cache1.cache_push(k);
    }
    runner.test(matches, 4);

    matches = 0;
    el_amt = 10;
    std::vector<int> reqs2 = {1, 2, 3, 1, 2, 3, 4, 4, 4, 7};
    LFUCache cache2(5, reqs2);
    for (int i = 0; i < el_amt; i++)
    {
        int k = reqs2[i];
        matches = cache2.cache_push(k);
    }
    runner.test(matches, 5);

    matches = 0;
    el_amt = 9;
    std::vector<int> reqs3 = {1, 2, 3, 7, 2, 5, 3, 5, 1};
    LFUCache cache3(3, reqs3);
    for (int i = 0; i < el_amt; i++)
    {
        int k = reqs3[i];
        matches = cache3.cache_push(k);
    }
    runner.test(matches, 2);

    runner.print_results();
}