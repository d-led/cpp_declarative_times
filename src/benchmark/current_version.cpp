#include "times_fixture.h"

#include <declarative_times.h>

#include <functional>

using namespace declarative_times;

struct Current_TimesVsLoop : TimesVsLoop {};

BENCHMARK_F(Current_TimesVsLoop, Times_Without_Index, 10, 100)
{
    1000000_times([]{
        do_something();
    });
}

BENCHMARK_F(Current_TimesVsLoop, Loop_Without_Index, 10, 100)
{
    for (auto i = 0; i < 1000000; i++) {
       do_something();
    }
}

BENCHMARK_F(Current_TimesVsLoop, Times_With_Index, 10, 100)
{
    1000000_times_with_index([](unsigned long long i){
        do_something(i);
    });
}

BENCHMARK_F(Current_TimesVsLoop, Loop_With_Index, 10, 100)
{
    for (auto i = 0; i < 1000000; i++) {
       do_something(i);
    }
}
