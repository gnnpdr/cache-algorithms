#include <iostream>
#include <set>
#include <unordered_map>
#include <vector>

const size_t MAX_CACHE_SIZE = 200;

class BeladyCache
{
private:

    struct CacheCell
    {
        int key;
        int next_pos;

        bool operator<(const CacheCell& other) const
        {
            return next_pos >= other.next_pos;
        }
    };

    std::vector<int> requests;
    std::set<CacheCell> cache_set;
    std::unordered_map<int, std::set<CacheCell>::iterator> cells_table; 
    size_t capacity = 0;
    size_t cur_pos = 0;
    size_t total_match_cnt = 0;

    using the_cell = std::set<CacheCell>::iterator;

public:

    BeladyCache(size_t capacity, std::vector<int> requests) : capacity(capacity), requests(requests) {}

    size_t cache_push(int key)
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

        //print_cache();
        //std::cout << std::endl;

        return total_match_cnt;
    } 

private:

    the_cell list_move(int key)
    {
        auto it = cells_table.find(key);
        CacheCell the_cell = *it->second;
        cache_set.erase(it->second);
        the_cell.next_pos = find_next_pos(key, cur_pos + 1);

        if (find_next_pos(key, cur_pos + 1) == MAX_CACHE_SIZE)
            the_cell.next_pos = MAX_CACHE_SIZE;

        return cache_set.insert(the_cell).first;
    }

    the_cell list_push(int key)
    {
        if (cache_set.size() >= capacity)
            del_page();

        CacheCell new_cell{key, find_next_pos(key, cur_pos + 1)};
        if (find_next_pos(key, cur_pos + 1) == MAX_CACHE_SIZE)
            new_cell.next_pos = MAX_CACHE_SIZE;

        return cache_set.insert(new_cell).first;
    }

    void del_page()
    {
        auto del_cell = cache_set.begin();
        cells_table.erase(del_cell->key);
        cache_set.erase(del_cell);
    }

    int find_next_pos(int key, size_t cur_pos)
    {
        for (size_t pos = cur_pos; pos < requests.size(); pos++)
        {
            if (key == requests[pos])
                return pos;
        }

        return MAX_CACHE_SIZE;
    }

    void print_cache()
    {
        for (const auto& element : cache_set)
            std::cout << element.key << " " ;
        
        std::cout << std::endl;
    }
};

class TestRunner
{
private:
    size_t total_test_amt = 0;
    size_t passed_test_amt = 0;

public:

    void test(size_t res, size_t expected_res)
    {
        total_test_amt++;
        if (res == expected_res)
            passed_test_amt++;
        else
        {
            std::cout << "test " << total_test_amt << " failed. " << "Expected " << expected_res << " Received " << res << std::endl;
        }
    }

    void print_results()
    {
        if (total_test_amt != passed_test_amt)
        {
            std::cout << passed_test_amt << " out of " << total_test_amt << " tests passed\nDO SOMETHING WITH IT" << std::endl;

        }
        else
            std::cout << "ALL TESTS PASSED CONGRATULATIONS!" << std::endl;
    }
};

void run_Belady_tests()
{
    TestRunner runner;
    size_t matches = 0;

    size_t el_amt = 6;
    std::vector<int> reqs1 = {1, 2, 1, 2, 1, 2};
    BeladyCache cache1(2, reqs1);

    for (int i = 0; i < 2; i++)
    {
        int k = reqs1[i];
        matches = cache1.cache_push(k);
    }
    runner.test(matches, 0);

    for (int i = 2; i < el_amt; i++) 
    {
        int k = reqs1[i];
        matches = cache1.cache_push(k);
    }
    runner.test(matches, 4);

    std::cout << std::endl;
    matches = 0;
    el_amt = 10;
    std::vector<int> reqs2 = {1, 2, 3, 1, 2, 3, 4, 4, 4, 7};
    BeladyCache cache2(5, reqs2);
    for (int i = 0; i < el_amt; i++)
    {
        int k = reqs2[i];
        matches = cache2.cache_push(k);
    }
    runner.test(matches, 5);

    std::cout << std::endl;
    matches = 0;
    el_amt = 9;
    std::vector<int> reqs3 = {1, 2, 3, 7, 2, 5, 3, 5, 1};
    BeladyCache cache3(3, reqs3);
    for (int i = 0; i < el_amt; i++)
    {
        int k = reqs3[i];
        matches = cache3.cache_push(k);
    }
    runner.test(matches, 3);

    runner.print_results();
}


int main()
{
    //size_t cap = 0;
    //std::cout << "enter capacity" << std::endl;
    //std::cin >> cap;
    //size_t el_amt = 0;
    //std::cout << "enter elements amount" << std::endl;
    //std::cin >> el_amt;
    //std::vector<int> reqs;
    //std::cout << "enter elements" << std::endl;
    //for (int i = 0; i < el_amt; i++)
    //{
    //    int k = 0;
    //
    //    std::cin >> k;
    //    reqs.push_back(k);
    //}
    //BeladyCache cache(cap, reqs);
    //size_t matches = 0;
    //for (int i = 0; i < el_amt; i++)
    //{
    //    int k = reqs[i];
    //    matches = cache.cache_push(k);
    //}
    //std::cout << "matches: " << matches << std::endl; 

    //run_Belady_tests();
    
    return 0;
}