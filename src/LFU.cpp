#include "../include/LFU.hpp"

LFUCache::LFUCache(size_t capacity, size_t el_amt, std::vector<int> requests) : capacity(capacity), el_amt(el_amt), requests(requests) {}
using the_cell = std::set<LFUCache::CacheCell>::iterator;

size_t LFUCache::cache_push(int key)
{
    the_cell new_cell_it;

    auto it = cells_table.find(key);
    if (it == cells_table.end())
    {
        new_cell_it = list_push(key);
    }
    else
    {
        total_match_cnt++;
        new_cell_it = list_move(key);
    }
    cells_table[key] = new_cell_it;

    return total_match_cnt;
} 

the_cell LFUCache::list_move(int key)
{
    auto it = cells_table.find(key);
    CacheCell the_cell = *it->second;
    cache_set.erase(it->second);
    the_cell.match_cnt++;

    return cache_set.insert(the_cell).first;
}

the_cell LFUCache::list_push(int key)
{
    if (cache_set.size() >= capacity)
        del_page();
    CacheCell new_cell{key, START_MATCH_VAL};

    return cache_set.insert(new_cell).first;
}

void LFUCache::del_page()
{
    auto del_cell = cache_set.begin();
    cells_table.erase(del_cell->key);
    cache_set.erase(del_cell);
}