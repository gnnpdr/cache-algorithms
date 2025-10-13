#include "include/Belady.hpp"
#include "include/LFU.hpp"
#include "include/tests.hpp"

int main()
{
    std::cout << "Please, enter data for Belady cache: capacity, amount of elements and elements" << std::endl;
    size_t cap = 0;
    std::cin >> cap;
    size_t el_amt = 0;
    std::cin >> el_amt;
    std::vector<int> reqs1;
    for (int i = 0; i < el_amt; i++)
    {
        int k = 0;
        std::cin >> k;
        reqs1.push_back(k);
    }
    BeladyCache cache1(cap, reqs1);
    size_t matches = 0;
    for (int i = 0; i < el_amt; i++)
    {
        int k = reqs1[i];
        matches = cache1.cache_push(k);
    }
    std::cout << "matches: " << matches << std::endl; 

    //run_Belady_tests();

    std::cout << "Please, enter data for LFU cache: capacity, amount of elements and elements" << std::endl;
    std::cin >> cap;
    std::cin >> el_amt;
    std::vector<int> reqs2;
    for (int i = 0; i < el_amt; i++)
    {
        int k = 0;
        std::cin >> k;
        reqs2.push_back(k);
    }
    LFUCache cache2(cap, reqs2);
    matches = 0;
    for (int i = 0; i < el_amt; i++)
    {
        int k = reqs2[i];
        matches = cache2.cache_push(k);
    }
    std::cout << "matches: " << matches << std::endl; 

    //run_LFU_tests();
    
    return 0;
}