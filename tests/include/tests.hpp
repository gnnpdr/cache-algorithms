#pragma once

#include "../include/common.hpp"

struct TestData
{
    size_t capacity;
    size_t el_amt;
    std::vector<int> reqs;
    size_t match_amt;
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

    static std::vector<TestData> LFU_tests = {
                            {3, 15, {1 ,2 ,3 ,4 ,1 ,2 ,5 ,3 ,1 ,6 ,4 ,2 ,7 ,3 ,8}, 4},
                            {4, 17, {1 ,2 ,3 ,4 ,5 ,1 ,2 ,6 ,3 ,7 ,4 ,8 ,5 ,9 ,1 ,10 ,2}, 5},
                            {3, 15, {1 ,2 ,3 ,2 ,1 ,4 ,3 ,5 ,1 ,2 ,6 ,4 ,7 ,3 ,8}, 4},
                            {5, 18, {1 ,2 ,3 ,4 ,5 ,6 ,7 ,1 ,8 ,2 ,9 ,3 ,10 ,4 ,11 ,5 ,12 ,6}, 4},
                            {3, 18, {1 ,2 ,1 ,3 ,1 ,4 ,1 ,5 ,1 ,6 ,1 ,7 ,1 ,8 ,1 ,9 ,1 ,10}, 8},
                            {4, 18, {1 ,2 ,3 ,4 ,1 ,2 ,5 ,6 ,3 ,4 ,7 ,8 ,1 ,2 ,9 ,10 ,3 ,4}, 6},
                            {3, 17, {1 ,2 ,3 ,4 ,3 ,2 ,5 ,1 ,6 ,4 ,7 ,2 ,8 ,3 ,9 ,1 ,10}, 4},
                            {5, 18, {1 ,2 ,3 ,4 ,5 ,6 ,7 ,8 ,9 ,10 ,1 ,2 ,3 ,4 ,5 ,11 ,12 ,13}, 4},
                            {3, 18, {1 ,2 ,3 ,1 ,4 ,2 ,5 ,3 ,6 ,1 ,7 ,2 ,8 ,3 ,9 ,1 ,10 ,2}, 6},
                            {4, 20, {1 ,2 ,3 ,1 ,4 ,2 ,5 ,3 ,6 ,1 ,7 ,4 ,8 ,2 ,9 ,5 ,10 ,3 ,11 ,1}, 7}};
}

template<typename CacheType>
struct TestDataSelector;

template<>
struct TestDataSelector<BeladyCache> 
{
    static const std::vector<TestData>& get_tests_data() 
    {
        return TestDataStorage::Belady_tests;
    }
};

template<>
struct TestDataSelector<LFUCache> 
{
    static const std::vector<TestData>& get_tests_data() 
    {
        return TestDataStorage::LFU_tests;
    }
};


template<typename CacheType>
class TestRunner
{
private:
    size_t total_test_amt = 0;
    size_t passed_test_amt = 0;
    const std::vector<TestData>& tests = TestDataSelector<CacheType>::get_tests_data();
public:

    TestRunner() = default;

    void run_tests();
    void single_test(TestData test);
    void print_results();
};

template<typename CacheType>
void TestRunner<CacheType>::run_tests()
{
    const auto& tests = TestDataSelector<CacheType>::get_tests_data();
    for (const TestData& test : tests)
        single_test(test);

    print_results();
}

template<typename CacheType>
void TestRunner<CacheType>::single_test(TestData test)
{
    total_test_amt++;

    size_t cap = test.capacity;
    size_t el_amt = test.el_amt;
    size_t match_amt = test.match_amt;
    std::vector<int> reqs = test.reqs;
    auto cache = CacheType(cap, el_amt, reqs);

    size_t matches = run_cache(cache);

    if (matches != test.match_amt)
        std::cout << "test " << total_test_amt << " failed. " << "Expected " << test.match_amt << " Received " << matches << std::endl;
    else
    {
        passed_test_amt++;
        //std::cout << "test " << total_test_amt << " is good" << std::endl;
    }
}

template<typename CacheType>
void TestRunner<CacheType>::print_results()
{
    if (total_test_amt != passed_test_amt)
    {
        std::cout << passed_test_amt << " out of " << total_test_amt << " tests passed" << std::endl;
    }
    else
        std::cout << "ALL TESTS PASSED!" << std::endl;
}