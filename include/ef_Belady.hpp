#pragma once

#include "Belady.hpp"

class EfBeladyCache
{
public:
    struct CacheCell
    {
        int key;
        size_t next_pos;

        bool operator<(const CacheCell& other) const
        {
            return next_pos >= other.next_pos;
        }
    };
    using the_cell = std::set<CacheCell>::iterator;

private:
    size_t capacity = 0;
    size_t cur_pos = 0;
    size_t total_match_cnt = 0;
    size_t el_amt = 0;

    std::vector<int> requests;
    std::set<CacheCell> cache_set;
    std::unordered_map<int, std::set<CacheCell>::iterator> cells_table; 

public:
    EfBeladyCache(size_t capacity, size_t el_amt, std::vector<int> requests);

    size_t cache_push(int key);
    the_cell list_move(int key);
    the_cell list_push(int key);
    void del_page();
    size_t find_next_pos(int key, size_t cur_pos);

    size_t get_el_amt() const {return el_amt;}
    const std::vector<int>& get_requests() const {return requests;}
    const std::set<CacheCell>& get_cache_set() const {return cache_set;}
};