#pragma once

#include "Belady.hpp"

const size_t START_MATCH_VAL = 1;

template<typename KeyT = int, typename ValT = KeyT>
class LFUCache
{
    size_t capacity_ = 0;

public:
    using key_type = KeyT;

    struct CacheCell
    {
        KeyT key;
        ValT val;
        size_t match_cnt;

        bool operator<(const CacheCell& other) const
        {
            return match_cnt <= other.match_cnt;
        }
    };
    using the_cell = typename std::set<CacheCell>::iterator;

private:
    std::vector<KeyT> requests_;
    std::set<CacheCell> cache_;
    std::unordered_map<KeyT, the_cell> hash_; 

public:
    explicit LFUCache(size_t capacity) : capacity_(capacity) {}

    template<typename F> 
    bool lookup_update(KeyT key, F slow_get_page)
    {
        auto it = hash_.find(key);
        if (it == hash_.end())
        {
            ValT val = slow_get_page(key);
            load_cache_cell(key, val);
            return false;
        }
        else
        {
            update_cache_cell(key);
            return true;
        }
    }

    //const std::set<CacheCell>& get_cache() const {return cache_;}

private:
    void update_cache_cell(KeyT key)
    {
        auto it = hash_.find(key);
        CacheCell the_cell = *it->second;
        cache_.erase(it->second);

        the_cell.match_cnt++;

        auto new_cell_it = cache_.insert(the_cell).first;
        it->second = new_cell_it;
    }

    void load_cache_cell(KeyT key, ValT val)
    {
        if (cache_.size() >= capacity_)
            del_page();

        CacheCell new_cell{key, val, START_MATCH_VAL};

        auto new_cell_it = cache_.insert(new_cell).first;
        hash_[key] = new_cell_it;
    }

    void del_page()
    {
        auto del_cell = cache_.begin();
        hash_.erase(del_cell->key);
        cache_.erase(del_cell);
    }
};