#include "../include/Belady.hpp"

BeladyCache::BeladyCache(size_t capacity, std::vector<int> requests) : capacity(capacity), requests(requests) {}
using the_cell = std::set<BeladyCache::CacheCell>::iterator;

size_t BeladyCache::cache_push(int key)
{
    cur_pos++;
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

the_cell BeladyCache::list_move(int key)
{
    auto it = cells_table.find(key);
    CacheCell the_cell = *it->second;
    cache_set.erase(it->second);

    the_cell.next_pos = find_next_pos(key, cur_pos + 1);
    if (find_next_pos(key, cur_pos + 1) == MAX_CACHE_SIZE)
        the_cell.next_pos = MAX_CACHE_SIZE;

    return cache_set.insert(the_cell).first;
}

the_cell BeladyCache::list_push(int key)
{
    if (cache_set.size() >= capacity)
        del_page();

    CacheCell new_cell{key, find_next_pos(key, cur_pos + 1)};
    if (find_next_pos(key, cur_pos + 1) == MAX_CACHE_SIZE)
        new_cell.next_pos = MAX_CACHE_SIZE;

    return cache_set.insert(new_cell).first;
}

void BeladyCache::del_page()
{
    auto del_cell = cache_set.begin();
    cells_table.erase(del_cell->key);
    cache_set.erase(del_cell);
}

int BeladyCache::find_next_pos(int key, size_t cur_pos)
{
    for (size_t pos = cur_pos; pos < requests.size(); pos++)
    {
        if (key == requests[pos])
            return pos;
    }
    return MAX_CACHE_SIZE;
}

void BeladyCache::print_cache()
{
    for (const auto& element : cache_set)
        std::cout << element.key << " " ;
    
    std::cout << std::endl;
}

