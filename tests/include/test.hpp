#pragma once

#include "../include/common.hpp"
#include <chrono>

const char* BIG_TEST_FILE_NAME = "tests/include/big_test.dat";

struct TestData
{
    size_t capacity;
    size_t reqs_amt;
    std::vector<int> reqs;
    size_t hits_amt;
};

namespace TestDataStorage
{
    static std::vector<TestData> Belady_tests = {
                            {3, 15, {1 ,2 ,3 ,4 ,1 ,2 ,5 ,3 ,1 ,6 ,4 ,2 ,7 ,3 ,8}, 6},
                            {4, 17, {1 ,2 ,3 ,4 ,5 ,1 ,2 ,6 ,3 ,7 ,4 ,8 ,5 ,9 ,1 ,10 ,2}, 6},
                            {3, 15, {1 ,2 ,3 ,2 ,1 ,4 ,3 ,5 ,1 ,2 ,6 ,4 ,7 ,3 ,8}, 6},
                            {5, 18, {1 ,2 ,3 ,4 ,5 ,6 ,7 ,1 ,8 ,2 ,9 ,3 ,10 ,4 ,11 ,5 ,12 ,6}, 5},
                            {3, 18, {1 ,2 ,1 ,3 ,1 ,4 ,1 ,5 ,1 ,6 ,1 ,7 ,1 ,8 ,1 ,9 ,1 ,10}, 8},
                            {4, 18, {1 ,2 ,3 ,4 ,1 ,2 ,5 ,6 ,3 ,4 ,7 ,8 ,1 ,2 ,9 ,10 ,3 ,4}, 8},
                            {3, 17, {1 ,2 ,3 ,4 ,3 ,2 ,5 ,1 ,6 ,4 ,7 ,2 ,8 ,3 ,9 ,1 ,10}, 6},
                            {5, 18, {1 ,2 ,3 ,4 ,5 ,6 ,7 ,8 ,9 ,10 ,1 ,2 ,3 ,4 ,5 ,11 ,12 ,13}, 5},
                            {3, 18, {1 ,2 ,3 ,1 ,4 ,2 ,5 ,3 ,6 ,1 ,7 ,2 ,8 ,3 ,9 ,1 ,10 ,2}, 8},
                            {4, 20, {1 ,2 ,3 ,1 ,4 ,2 ,5 ,3 ,6 ,1 ,7 ,4 ,8 ,2 ,9 ,5 ,10 ,3 ,11 ,1}, 8},
                            {4, 12, {1 ,2 ,3 ,4 ,1, 2, 5, 1, 2, 4, 3, 4}, 7}};
}

template<typename CacheType>
struct TestDataSelector;

using BeladyCacheInt = BeladyCache<int, int>;

template<>
struct TestDataSelector<BeladyCacheInt> 
{
    static const std::vector<TestData>& get_tests_data() 
    {
        return TestDataStorage::Belady_tests;
    }
};

template<typename CacheType>
class TestRunner
{
    size_t total_test_amt = 0;
    size_t passed_test_amt = 0;
    const std::vector<TestData>& tests = TestDataSelector<CacheType>::get_tests_data();
public:

    void run_tests();
    void run_single_test(TestData test);
    void run_big_test();
    void print_tests_result();
};

template<typename CacheType>
void TestRunner<CacheType>::run_tests()
{
    const auto& tests = TestDataSelector<CacheType>::get_tests_data();
    for (const TestData& test : tests)
        run_single_test(test);

    print_tests_result();
}

template<typename CacheType>
void TestRunner<CacheType>::run_single_test(TestData test)
{
    total_test_amt++;

    size_t cap = test.capacity;
    size_t reqs_amt = test.reqs_amt;
    size_t hits_amt = test.hits_amt;
    std::vector<int> reqs = test.reqs;
    auto cache = CacheType(cap, reqs);

    size_t hits = run_cache(cache);

    if (hits != test.hits_amt)
        std::cout << "Test " << total_test_amt << " failed. " << "Expected " << test.hits_amt << " Received " << hits << std::endl;
    else
        passed_test_amt++;
}

template<typename CacheType>
void TestRunner<CacheType>::print_tests_result()
{
    if (total_test_amt != passed_test_amt)
        std::cout << passed_test_amt << " out of " << total_test_amt << " tests passed" << std::endl;
    else
        std::cout << "ALL TESTS PASSED!" << std::endl;
}

template<typename CacheType>
void TestRunner<CacheType>::run_big_test()
{   
    std::ifstream file_input(BIG_TEST_FILE_NAME);
    
    auto cache = cache_ctor<CacheType>(file_input);

    auto start = std::chrono::high_resolution_clock::now();

    size_t hits = run_cache(cache);

    auto end = std::chrono::high_resolution_clock::now();
    
    std::chrono::duration<double> time_taken = end - start;
    std::cout << "caching time: " << time_taken.count() << " seconds" << std::endl;

    size_t reqs_amt = cache.get_reqs_amt();
    print_hits_result(hits, reqs_amt);
}