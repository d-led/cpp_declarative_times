#include "times_fixture.h"

#include <functional>

namespace {

struct execute {
    const unsigned long long count;

    template<typename Callable>
    void operator() (Callable what) {
        for (auto i = 0; i < count; i++)
            what();
    }
};

struct execute_with_index {
    const unsigned long long count;

    template<typename CallableWithIndex>
    void operator() (CallableWithIndex what) {
        for (auto i = 0; i < count; i++)
            what(i);
    }
};

execute operator"" _times(unsigned long long count) {
    return { count };
}

execute_with_index operator"" _times_with_index(unsigned long long count) {
    return { count };
}

}

struct SimplerResolution_TimesVsLoop : TimesVsLoop {};

BENCHMARK_F(SimplerResolution_TimesVsLoop, Times_Without_Index, 10, 100)
{
    1000000_times([]{
        do_something();
    });
}

BENCHMARK_F(SimplerResolution_TimesVsLoop, Loop_Without_Index, 10, 100)
{
    for (auto i = 0; i < 1000000; i++) {
       do_something();
    }
}

BENCHMARK_F(SimplerResolution_TimesVsLoop, Times_With_Index, 10, 100)
{
    1000000_times_with_index([](unsigned long long i){
        do_something(i);
    });
}

BENCHMARK_F(SimplerResolution_TimesVsLoop, Loop_With_Index, 10, 100)
{
    for (auto i = 0; i < 1000000; i++) {
       do_something(i);
    }
}
