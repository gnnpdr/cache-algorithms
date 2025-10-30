#include "../include/Belady.hpp"

BeladyCache::BeladyCache(size_t capacity, size_t reqs_amt, std::vector<int> requests) : capacity(capacity), reqs_amt(reqs_amt), requests(requests) 
{
    fill_key_positions();
}

using the_cell = std::set<BeladyCache::CacheCell>::iterator;

void BeladyCache::fill_key_positions() 
{
    size_t reqs_size = requests.size();
    for (size_t pos = 0; pos < reqs_size; pos++)
    {
        key_positions[requests[pos]].push_back(pos);
        next_pos_ind.insert({requests[pos], 0});
    }
}

size_t BeladyCache::cache_push(int key)
{
    cur_pos++;
    the_cell new_cell_it;
        
    auto it = cells_table.find(key);
    if (it == cells_table.end())
    {
        size_t next_pos = find_next_pos(key);
        if (next_pos == MAX_CACHE_SIZE)
        {
            next_pos_ind[key]++;
            return total_match_cnt;
        }
        else if (cache_set.size() >= capacity && next_pos > cache_set.begin()->next_pos)
        {
            next_pos_ind[key]++;
            return total_match_cnt;
        }
            
        new_cell_it = list_push(key);
    }
    else
    {
        total_match_cnt++;
        new_cell_it = list_move(key);
    }
    cells_table[key] = new_cell_it;
    next_pos_ind[key]++;

    return total_match_cnt;
} 

the_cell BeladyCache::list_move(int key)
{
    auto it = cells_table.find(key);
    CacheCell the_cell = *it->second;
    cache_set.erase(it->second);

    the_cell.next_pos = find_next_pos(key);

    return cache_set.insert(the_cell).first;
}

the_cell BeladyCache::list_push(int key)
{
    if (cache_set.size() >= capacity)
        del_page();

    CacheCell new_cell{key, find_next_pos(key)};

    return cache_set.insert(new_cell).first;
}

void BeladyCache::del_page()
{
    auto del_cell = cache_set.begin();
    cells_table.erase(del_cell->key);
    cache_set.erase(del_cell);
}

size_t BeladyCache::find_next_pos(int key)
{
    auto& pos_arr = key_positions.find(key)->second;

    if (pos_arr[next_pos_ind.find(key)->second] == cur_pos - 1 && next_pos_ind.find(key)->second + 1 == pos_arr.size())
        return MAX_CACHE_SIZE;
    else if (pos_arr[next_pos_ind.find(key)->second] == cur_pos - 1)
        return pos_arr[next_pos_ind.find(key)->second + 1];
    else
        return pos_arr[next_pos_ind.find(key)->second];
}