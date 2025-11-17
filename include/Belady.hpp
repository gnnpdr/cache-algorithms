#pragma once

#include <iostream>
#include <set>
#include <unordered_map>
#include <vector>
#include <limits>

namespace Belady
{
namespace consts
{
const size_t MAX_CACHE_SIZE = std::numeric_limits<size_t>::max();
}

template<typename KeyT = int, typename ValT = KeyT>
class BeladyCache
{
    size_t capacity_ = 0;
    size_t cur_pos_ = 0;

public:
    using key_type = KeyT;

    struct CacheCell
    {
        KeyT key;
        ValT val;
        size_t next_pos;

        auto operator<=>(const CacheCell& other) const
        {
            return other.next_pos <=> next_pos;
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
            if (next_pos == consts::MAX_CACHE_SIZE)
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
    
private:
    void update_cache_cell(KeyT key)
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
        auto pos_it = key_positions_.find(key);
        auto ind_it = next_pos_ind_.find(key);

        if (pos_it == key_positions_.end() || ind_it == next_pos_ind_.end()) 
            return consts::MAX_CACHE_SIZE;

        auto& pos_arr = pos_it->second;
        size_t current_index = ind_it->second;

        if (current_index >= pos_arr.size()) 
            return consts::MAX_CACHE_SIZE;

        if (pos_arr[current_index] == cur_pos_ - 1) 
        {
            current_index++;
            if (current_index >= pos_arr.size()) 
                return consts::MAX_CACHE_SIZE;
        }

        return pos_arr[current_index];
    }

    void del_page()
    {
        if (cache_.empty())
            return;

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

}