#pragma once

#include "../include/common.hpp"
#include "tests_common.hpp"
#include <chrono>
#include <functional>

//---------------------------------------------------------------------------------------------------


namespace TestDataStorage
{
    static std::vector<TestData<int>> Belady_tests_int = {
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

    static std::vector<TestData<double>> Belady_tests_double = {
                            {3, 8, {1.5, 2.7, 1.5, 3.14, 2.7, 4.2, 1.5, 3.14}, 4},
                            {2, 7, {-1.5, 0.0, 2.5, -1.5, 0.0, 3.7, -2.1}, 2},
                            {2, 6, {1.0000001, 1.0000002, 1.0000001, 2.5, 1.0000002, 3.0}, 2}};

    static std::vector<TestData<std::string>> Belady_tests_string = {
                            {3, 7, {"home", "about", "home", "contact", "about", "products", "home"}, 3}};
}

template<typename KeyT>
struct BeladyTestDataSelector;

template<>
struct BeladyTestDataSelector<int> 
{
    static const std::vector<TestData<int>>& get_tests_data() 
    {
        return TestDataStorage::Belady_tests_int;
    }
};

template<>
struct BeladyTestDataSelector<double> 
{
    static const std::vector<TestData<double>>& get_tests_data() 
    {
        return TestDataStorage::Belady_tests_double;
    }
};

template<>
struct BeladyTestDataSelector<std::string> 
{
    static const std::vector<TestData<std::string>>& get_tests_data() 
    {
        return TestDataStorage::Belady_tests_string;
    }
};



template<typename KeyT, typename ValT = int>
class BeladyTestRunner
{
    size_t total_test_amt = 0;
    size_t passed_test_amt = 0;
    const std::vector<TestData<KeyT>>& tests;
public:

    BeladyTestRunner() : tests(BeladyTestDataSelector<KeyT>::get_tests_data()) {}

    void run_tests();
    void run_single_test(TestData<KeyT> test);
    void run_big_test();
    void print_tests_result();
};

//-----------------------------------------------------------------------------------------------


template<typename KeyT, typename ValT>
void BeladyTestRunner<KeyT, ValT>::run_tests()
{
    const auto& tests = BeladyTestDataSelector<KeyT>::get_tests_data();
    for (const TestData<KeyT>& test : tests)
        run_single_test(test);

    print_tests_result();
}

template<typename KeyT, typename ValT>
void BeladyTestRunner<KeyT, ValT>::run_single_test(TestData<KeyT> test)
{
    total_test_amt++;

    size_t cap = test.capacity;
    size_t reqs_amt = test.reqs_amt;
    size_t hits_amt = test.hits_amt;
    std::vector<KeyT> reqs = test.reqs;
    auto cache = BeladyCache<KeyT, ValT>(cap, reqs);

    size_t hits = run_Belady_cache(cache);

    if (hits != test.hits_amt)
        std::cout << "Test " << total_test_amt << " failed. " << "Expected " << test.hits_amt << " Received " << hits << std::endl;
    else
        passed_test_amt++;
}

template<typename KeyT, typename ValT>
void BeladyTestRunner<KeyT, ValT>::print_tests_result()
{
    if (total_test_amt != passed_test_amt)
        std::cout << passed_test_amt << " out of " << total_test_amt << " tests passed" << std::endl;
    else
        std::cout << "all tests passed!" << std::endl;
}

template<typename KeyT, typename ValT>
void BeladyTestRunner<KeyT, ValT>::run_big_test()
{   
    std::ifstream file_input(BIG_TEST_FILE_NAME);
    
    auto cache = Belady_cache_ctor<KeyT, ValT>(file_input);

    auto start = std::chrono::high_resolution_clock::now();

    size_t hits = run_Belady_cache<KeyT, ValT>(cache);

    auto end = std::chrono::high_resolution_clock::now();
    
    std::chrono::duration<double> time_taken = end - start;
    std::cout << "caching time: " << time_taken.count() << " seconds" << std::endl;

    auto reqs = cache.get_requests();
    size_t reqs_amt = reqs.size();
    print_hits_result(hits, reqs_amt);
}