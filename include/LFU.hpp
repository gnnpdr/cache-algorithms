#pragma once

#include "ef_Belady.hpp"

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

    size_t get_el_amt() const {return el_amt;}
    const std::vector<int>& get_requests() const {return requests;}
    const std::set<CacheCell>& get_cache_set() const {return cache_set;}
};