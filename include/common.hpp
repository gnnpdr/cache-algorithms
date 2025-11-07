#pragma once

//#include "LFU.hpp"
#include "B.hpp"

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

    return CacheType(cap,  reqs);
}
//
//template<typename CacheType>
//size_t run_cache(CacheType& cache)
//{
//    size_t reqs_amt = cache.get_reqs_amt();
//    auto reqs = cache.get_requests();
//
//    size_t hits = 0;
//    for (size_t req = 0; req < reqs_amt; req++)
//    {
//        int el = reqs[req];
//        bool is_hit = cache.cache_push(el);
//        if (is_hit)
//            hits++;
//    }
//
//    return hits;
//}

template<typename CacheType>
size_t run_cache(CacheType& cache)
{
    auto reqs = cache.get_requests();
    size_t reqs_amt = reqs.size();

    size_t hits = 0;
    for (size_t req = 0; req < reqs_amt; req++)
    {
        int key = reqs[req];
        
        bool is_hit = cache.lookup_update(key, slow_get_page_int);

        //auto cache_set = cache.get_cache();
        //for (const auto& element : cache_set)
        //{
        //    std::cout << "k " << element.key << " v " << element.val << " np" << element.next_pos << " / ";
        //}
//
        //std::cout << std::endl;
        
        if (is_hit)
            hits++;
    }

    return hits;
}

void print_hits_result(size_t hits, size_t reqs_amt)
{
    std::cout << "Hits: " << hits << std::endl;

    size_t hit_rate = std::round((float)hits / (float)reqs_amt * 100);
    std::cout << "Hit rate: " << hit_rate << "%" << std::endl;
}