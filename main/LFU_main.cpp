#include "../include/common.hpp"

int main()
{
    auto cache_data = LFU_cache_ctor<int, int>();
    size_t hits = run_LFU_cache(cache_data);

    auto& reqs = cache_data.reqs;
    size_t reqs_amt = reqs.size();
    print_hits_result(hits, reqs_amt);

    return 0;
}