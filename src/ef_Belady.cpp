#include "../include/ef_Belady.hpp"

EfBeladyCache::EfBeladyCache(size_t capacity, size_t reqs_amt, std::vector<int> requests) : capacity(capacity), reqs_amt(reqs_amt), requests(requests) 
{
    fill_key_positions();
}
using the_cell = std::set<EfBeladyCache::CacheCell>::iterator;

size_t EfBeladyCache::cache_push(int key)
{

    //std::unordered_map<int, size_t> next_pos_ind;                //содержит текущий индекс в массиве позиций для каждого ключа, чтобы было еще быстрее
    //std::unordered_map<int, std::vector<size_t>> key_positions; 
    //std::cout << key << " positions array ";
//
    //for (int i = 0; i < key_positions.find(key)->second.size(); i++)
    //    std::cout << key_positions.find(key)->second[i] << " ";
    //
    //std::cout << std::endl;
//
    //std::cout << key << " next pos index is " << next_pos_ind.find(key)->second << std::endl;


    cur_pos++;
    the_cell new_cell_it;
        
    auto it = cells_table.find(key);
    if (it == cells_table.end())
    {
        size_t next_pos = find_next_pos(key);       //для текущего нужна следующая позиция, а для остальных текущая 
        //printf("next pos %d\n", next_pos);
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

the_cell EfBeladyCache::list_move(int key)
{
    auto it = cells_table.find(key);
    CacheCell the_cell = *it->second;
    cache_set.erase(it->second);

    the_cell.next_pos = find_next_pos(key);
    if (find_next_pos(key) == MAX_CACHE_SIZE)
        the_cell.next_pos = MAX_CACHE_SIZE;

    return cache_set.insert(the_cell).first;
}

the_cell EfBeladyCache::list_push(int key)
{
    if (cache_set.size() >= capacity)
        del_page();

    CacheCell new_cell{key, find_next_pos(key)};

    return cache_set.insert(new_cell).first;
}

void EfBeladyCache::del_page()
{
    auto del_cell = cache_set.begin();
    cells_table.erase(del_cell->key);
    cache_set.erase(del_cell);
}

void EfBeladyCache::fill_key_positions() 
{
    size_t reqs_size = requests.size();
    for (size_t pos = 0; pos < reqs_size; pos++)
    {
        key_positions[requests[pos]].push_back(pos);        //при таком заполнении позиции поступают сортированными
        next_pos_ind.insert({requests[pos], 0});
    }
}

size_t EfBeladyCache::find_next_pos(int key)
{
    auto it = key_positions.find(key);
    auto& pos_arr = it->second;

    //printf("!!!!! ind %d next_pos %d next next pos %d !!!!!\n", next_pos_ind.find(key)->second, pos_arr[next_pos_ind.find(key)->second], pos_arr[next_pos_ind.find(key)->second + 1]);
    if (pos_arr[next_pos_ind.find(key)->second] == cur_pos - 1 && next_pos_ind.find(key)->second + 1 == pos_arr.size())
        return MAX_CACHE_SIZE;
    else if (pos_arr[next_pos_ind.find(key)->second] == cur_pos - 1)
        return pos_arr[next_pos_ind.find(key)->second + 1];
    else
        return pos_arr[next_pos_ind.find(key)->second];
}