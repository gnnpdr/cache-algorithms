#pragma once

#include "LFU.hpp"

template<typename CacheType>
CacheType cache_ctor()
{
    size_t cap = 0;
    std::cin >> cap;

    size_t el_amt = 0;
    std::cin >> el_amt;

    std::vector<int> reqs;
    for (size_t i = 0; i < el_amt; i++)
    {
        int k = 0;
        std::cin >> k;
        reqs.push_back(k);
    }

    return CacheType(cap, el_amt, reqs);
}

template<typename CacheType>
void print_cache(CacheType& cache)
{
    auto cache_set = cache.get_cache_set();
    for (const auto& element : cache_set)
        std::cout << element.key << " ";
    
    std::cout << std::endl;
}

template<typename CacheType>
size_t run_cache(CacheType& cache)
{
    size_t el_amt = cache.get_el_amt();
    auto reqs = cache.get_requests();

    size_t matches = 0;
    for (size_t i = 0; i < el_amt; i++)
    {
        int k = reqs[i];
        matches = cache.cache_push(k);
    }

    return matches;
}