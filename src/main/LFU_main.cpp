#include "../include/common.hpp"

int main()
{
    auto cache = cache_ctor<LFUCache>();

    size_t hits = run_cache(cache);

    std::cout << "Hits: " << hits << std::endl;

    size_t reqs_amt = cache.get_reqs_amt();
    size_t hit_rate = std::round((float)hits / (float)reqs_amt * 100);
    std::cout << "Hit rate: " << hit_rate << "%" << std::endl;

    return 0;
}