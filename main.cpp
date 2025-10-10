#include "include/Belady.hpp"
#include "include/LFU.hpp"
#include "include/tests.hpp"

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

    run_Belady_tests();

    //size_t cap = 0;
    //std::cin >> cap;
    //size_t el_amt = 0;
    //std::cin >> el_amt;
    //std::vector<int> reqs;
    //for (int i = 0; i < el_amt; i++)
    //{
    //    int k = 0;
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

    run_LFU_tests();
    
    return 0;
}