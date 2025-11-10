#pragma once

#include <chrono>
#include <functional>

const char* BIG_TEST_FILE_NAME = "tests/include/big_test.dat";

template<typename KeyT>
struct TestData
{
    size_t capacity;
    size_t reqs_amt;
    std::vector<KeyT> reqs;
    size_t hits_amt;
};