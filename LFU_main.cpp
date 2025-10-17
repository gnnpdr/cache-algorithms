#include "include/common.hpp"

int main()
{
    auto cache = cache_ctor<LFUCache>();

    size_t matches = run_cache(cache);
    std::cout << "matches: " << matches << std::endl;

    return 0;
}