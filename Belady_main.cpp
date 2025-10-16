#include "include/Belady.hpp"

int main()
{
    auto cache = Belady_cache_ctor();

    cache.run_cache();
    
    return 0;
}