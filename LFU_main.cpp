#include "include/LFU.hpp"

int main()
{
    auto cache = LFU_cache_ctor();

    cache.run_cache();
    
    return 0;
}