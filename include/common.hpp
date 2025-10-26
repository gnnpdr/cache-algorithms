#pragma once

#include "LFU.hpp"

template<typename CacheType>
CacheType cache_ctor(std::istream& input = std::cin)
{
    size_t cap = 0;
    input >> cap;

    size_t reqs_amt = 0;
    input >> reqs_amt;

    std::vector<int> reqs;
    for (size_t req = 0; req < reqs_amt; req++)
    {
        int el = 0;
        input >> el;
        reqs.push_back(el);
    }

    return CacheType(cap, reqs_amt, reqs);
}

template<typename CacheType>
size_t run_cache(CacheType& cache)
{
    size_t reqs_amt = cache.get_reqs_amt();
    auto reqs = cache.get_requests();

    size_t hits = 0;
    for (size_t req = 0; req < reqs_amt; req++)
    {
        int el = reqs[req];
        hits = cache.cache_push(el);
    }

    return hits;
}