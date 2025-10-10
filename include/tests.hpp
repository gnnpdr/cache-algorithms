#pragma once
#include "LFU.hpp"

class TestRunner
{
private:
    size_t total_test_amt = 0;
    size_t passed_test_amt = 0;

public:

    void test(size_t res, size_t expected_res);
    void print_results();
};

void run_Belady_tests();
void run_LFU_tests();