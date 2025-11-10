#pragma once

//#include "LFU.hpp"
#include "B.hpp"

#include <type_traits>
#include <string>

template<typename KeyT>
auto get_default_slow_get_page() {
    if constexpr (std::is_same_v<KeyT, int>) {
        return [](int key) -> int { 
            return key * 10;
        };
    } else if constexpr (std::is_same_v<KeyT, double>) {
        return [](double key) -> int { 
            return static_cast<int>(key * 100);
        };
    } else if constexpr (std::is_same_v<KeyT, std::string>) {
        return [](const std::string& key) -> int { 
            return key.length();
        };
    } else {
        return [](KeyT key) -> int { 
            return static_cast<int>(key);
        };
    }
}

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

template<typename CacheType>
size_t run_cache(CacheType& cache)
{
    using KeyT = typename CacheType::key_type; 
    auto reqs = cache.get_requests();
    size_t reqs_amt = reqs.size();
    auto slow_get_page = get_default_slow_get_page<KeyT>();

    size_t hits = 0;
    for (size_t req = 0; req < reqs_amt; req++)
    {
        KeyT key = reqs[req];
        
        bool is_hit = cache.lookup_update(key, slow_get_page);

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