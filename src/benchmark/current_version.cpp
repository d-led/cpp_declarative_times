#include "times_fixture.h"

#include <declarative_times.h>

#include <functional>

using namespace declarative_times;

struct CurrentVersion : TimesVsLoop {};

BENCHMARK_F(CurrentVersion, Without_Index, 10, 100)
{
    1000000_times([] {
        do_something();
    });
}

BENCHMARK_F(CurrentVersion, With_Index, 10, 100)
{
    1000000_times_with_index([](unsigned long long i) {
        do_something(i);
    });
}
