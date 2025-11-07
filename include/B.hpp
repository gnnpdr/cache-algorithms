#pragma once

#include <iostream>
#include <set>
#include <unordered_map>
#include <vector>
#include <limits>
#include <fstream>
#include <cmath>

const size_t MAX_CACHE_SIZE = std::numeric_limits<size_t>::max();

template<typename KeyT = int, typename ValT = KeyT>
class BeladyCache
{
    size_t capacity_ = 0;
    size_t cur_pos_ = 0;

public:
    struct CacheCell
    {
        KeyT key;
        ValT val;
        size_t next_pos;

        bool operator<(const CacheCell& other) const
        {
            return next_pos >= other.next_pos;
        }
    };
    using the_cell = typename std::set<CacheCell>::iterator;

private:
    
    std::vector<KeyT> requests_;
    std::set<CacheCell> cache_;
    std::unordered_map<KeyT, the_cell> hash_;

    std::unordered_map<KeyT, size_t> next_pos_ind_;
    std::unordered_map<KeyT, std::vector<size_t>> key_positions_;
public:

    BeladyCache(size_t capacity, const std::vector<KeyT>& requests) : capacity_(capacity), requests_(requests) 
    {
        fill_key_positions();
    }

    template<typename F> 
    bool lookup_update(KeyT key, F slow_get_page)
    {
        cur_pos_++;

        auto it = hash_.find(key);
        if (it == hash_.end())
        {
            size_t next_pos = find_next_pos(key);
            if (next_pos == MAX_CACHE_SIZE)
            {
                next_pos_ind_[key]++;
                return false;
            }
            else if (cache_.size() >= capacity_ && next_pos > cache_.begin()->next_pos)
            {
                next_pos_ind_[key]++;
                return false;
            }

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

    const std::vector<KeyT>& get_requests() const {return requests_;}
    const std::set<CacheCell>& get_cache() const {return cache_;}

private:
    void update_cache_cell(int key)
    {
        auto it = hash_.find(key);
        CacheCell the_cell = *it->second;
        cache_.erase(it->second);

        the_cell.next_pos = find_next_pos(key);

        auto new_cell_it = cache_.insert(the_cell).first;
        it->second = new_cell_it;
        next_pos_ind_[key]++;
    }

    void load_cache_cell(KeyT key, ValT val)
    {
        if (cache_.size() >= capacity_)
            del_page();

        CacheCell new_cell{key, val, find_next_pos(key)};

        auto new_cell_it = cache_.insert(new_cell).first;
        hash_[key] = new_cell_it;
        next_pos_ind_[key]++;
    }

    size_t find_next_pos(KeyT key)
    {
        auto& pos_arr = key_positions_.find(key)->second;

        if (pos_arr[next_pos_ind_.find(key)->second] == cur_pos_ - 1 && next_pos_ind_.find(key)->second + 1 == pos_arr.size())
            return MAX_CACHE_SIZE;
        else if (pos_arr[next_pos_ind_.find(key)->second] == cur_pos_ - 1)
            return pos_arr[next_pos_ind_.find(key)->second + 1];
        else
            return pos_arr[next_pos_ind_.find(key)->second];
    }

    void del_page()
    {
        auto del_cell = cache_.begin();
        hash_.erase(del_cell->key);
        cache_.erase(del_cell);
    }

    void fill_key_positions() 
    {
        size_t reqs_size = requests_.size();
        for (size_t pos = 0; pos < reqs_size; pos++)
        {
            key_positions_[requests_[pos]].push_back(pos);
            next_pos_ind_.insert({requests_[pos], 0});
        }
    }

    
};


int slow_get_page_int(int key)
{
    return key * 10;
}