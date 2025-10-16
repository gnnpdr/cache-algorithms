#pragma once

#include <iostream>
#include <set>
#include <unordered_map>
#include <vector>

const size_t MAX_CACHE_SIZE = 200;
const size_t START_MATCH_VAL = 1;

class LFUCache
{
public:
    struct CacheCell
    {
        int key;
        int match_cnt;

        bool operator<(const CacheCell& other) const
        {
            return match_cnt <= other.match_cnt;
        }
    };
    using the_cell = std::set<CacheCell>::iterator;

private:
    std::vector<int> requests;
    std::set<CacheCell> cache_set;
    std::unordered_map<int, std::set<CacheCell>::iterator> cells_table; 
    size_t capacity = 0;
    size_t el_amt = 0;
    size_t total_match_cnt = 0;

public:
    LFUCache(size_t capacity, size_t el_amt, std::vector<int> requests);

    size_t cache_push(int key);
    the_cell list_move(int key);
    the_cell list_push(int key);
    void del_page();
    void print_cache();
    void LFUCache::run_cache();
};

LFUCache LFU_cache_ctor();