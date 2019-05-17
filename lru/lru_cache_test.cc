#include <iostream>
#include <chrono>

//#include "lru_cache_v1.h"
//#include "lru_cache_v2.h"
#include "lru_cache_v3.h"
#include "performance_statics.h"


static void UnitTest() {
    LRUCache cache{5};
    std::cout << cache << std::endl;

    auto value = cache.Get(1);
    std::cout << "value[1]: " << value << std::endl;

    cache.Set(1, 10);
    cache.Set(2, 20);
    cache.Set(3, 30);
    cache.Set(4, 40);
    cache.Set(5, 50);
    cache.Set(6, 60);
    std::cout << cache << std::endl;

    value = cache.Get(2);
    std::cout << "value[2]: " << value << std::endl;
    cache.Set(7, 70);
    std::cout << cache << std::endl;

    cache.Set(4, 400);
    cache.Set(8, 80);
    std::cout << cache << std::endl;

    cache.PrintUseCount();
}


static void PerformanceTest() {
    unsigned cache_size = 50000;
    LRUCache cache{cache_size};
    unsigned i = 1;
    for (; i!=cache_size+1; ++i) {
        cache.Set(i, i*10);
    }

    using algorithm::performance::Duration;
    using MicroDuration = Duration<microseconds>;
    {
        MicroDuration duration;
        cache.Set(i, i*10);
    }
    std::cout << "cost " << MicroDuration::GetDuration() 
        << " microseconds"<< std::endl;

    {
        MicroDuration duration;
        cache.Get(cache_size/2);
    }
    std::cout << "cost " << MicroDuration::GetDuration() 
        << " microseconds"<< std::endl;
}

int main() {
    UnitTest();
    PerformanceTest();

    return 0;
}
