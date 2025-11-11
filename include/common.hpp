#pragma once

#include "LFU.hpp"

#include <type_traits>
#include <cmath>
#include <string>
#include <fstream>

template<typename KeyT>
auto get_default_slow_get_page() 
{
    if constexpr (std::is_same_v<KeyT, int>) 
    {
        return [](int key) -> int 
        { 
            return key * 10;
        };
    } 
    else if constexpr (std::is_same_v<KeyT, double>) 
    {
        return [](double key) -> int 
        { 
            return static_cast<int>(key * 100);
        };
    } 
    else if constexpr (std::is_same_v<KeyT, std::string>) 
    {
        return [](const std::string& key) -> int 
        { 
            return key.length();
        };
    } 
    else 
    {
        return [](KeyT key) -> int 
        { 
            return static_cast<int>(key);
        };
    }
}

template<typename KeyT = int, typename ValT = int>
BeladyCache<KeyT, ValT> Belady_cache_ctor(std::istream& input = std::cin)
{
    size_t cap = 0;
    input >> cap;

    size_t reqs_amt = 0;
    input >> reqs_amt;

    std::vector<KeyT> reqs;
    for (size_t req = 0; req < reqs_amt; req++)
    {
        KeyT el = 0;
        input >> el;
        reqs.push_back(el);
    }

    return BeladyCache<KeyT, ValT>(cap,  reqs);
}

template<typename KeyT = int, typename ValT = int>
struct LFUCacheData
{
    LFUCache<KeyT, ValT> cache;
    std::vector<KeyT> reqs;
};

template<typename KeyT = int, typename ValT = int>
LFUCacheData<KeyT, ValT> LFU_cache_ctor(std::istream& input = std::cin)
{
    size_t cap = 0;
    input >> cap;

    size_t reqs_amt = 0;
    input >> reqs_amt;

    std::vector<KeyT> reqs;
    for (size_t req = 0; req < reqs_amt; req++)
    {
        KeyT el = 0;
        input >> el;
        reqs.push_back(el);
    }

    return {LFUCache<KeyT, ValT>(cap), reqs};
}

template<typename KeyT = int, typename ValT = int>
size_t run_Belady_cache(BeladyCache<KeyT, ValT> cache)
{
    auto reqs = cache.get_requests();
    size_t reqs_amt = reqs.size();
    auto slow_get_page = get_default_slow_get_page<KeyT>();

    size_t hits = 0;
    for (const auto& key : reqs)
    {
        bool is_hit = cache.lookup_update(key, slow_get_page);
        
        if (is_hit)
            hits++;
    }

    return hits;
}

template<typename KeyT = int, typename ValT = int>
size_t run_LFU_cache(LFUCacheData<KeyT, ValT> data)
{
    auto& cache = data.cache;
    auto& reqs = data.reqs;
    size_t reqs_amt = reqs.size();
    
    auto slow_get_page = get_default_slow_get_page<KeyT>();

    size_t hits = 0;
    for (const auto& key : data.reqs)
    {
        bool is_hit = cache.lookup_update(key, slow_get_page);
        
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