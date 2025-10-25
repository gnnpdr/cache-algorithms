#include "include/common.hpp"

int main()
{
    //printf("here\n");
    auto cache = cache_ctor<BeladyCache>();

    //printf("here\n");
    size_t matches = run_cache(cache);
    std::cout << "matches: " << matches << std::endl;

    return 0;
}