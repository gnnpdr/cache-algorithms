#include "../include/common.hpp"

int main()
{
    auto cache = Belady_cache_ctor<int, int>();

    size_t hits = run_Belady_cache(cache);

    auto reqs = cache.get_requests();
    size_t reqs_amt = reqs.size();
    print_hits_result(hits, reqs_amt);

    return 0;
}