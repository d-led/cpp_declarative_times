#include "times_fixture.h"

#include <functional>

namespace {

struct execute {
    const unsigned long long n;

    void operator() (std::function<void()> what) {
        for (auto i = 0; i < n; i++)
            what();
    }

    void operator() (std::function<void(unsigned long long)> what) {
        for (auto i = 0; i < n; i++)
            what(i);
    }
};

execute operator"" _times(unsigned long long n) {
    return execute{n};
}

}

struct StdFunction_TimesVsLoop : TimesVsLoop {};

BENCHMARK_F(StdFunction_TimesVsLoop, Times_Without_Index, 10, 100)
{
    1000000_times([]{
        do_something();
    });
}

BENCHMARK_F(StdFunction_TimesVsLoop, Loop_Without_Index, 10, 100)
{
    for (auto i = 0; i < 1000000; i++) {
       do_something();
    }
}

BENCHMARK_F(StdFunction_TimesVsLoop, Times_With_Index, 10, 100)
{
    1000000_times([](unsigned long long i){
        do_something(i);
    });
}

BENCHMARK_F(StdFunction_TimesVsLoop, Loop_With_Index, 10, 100)
{
    for (auto i = 0; i < 1000000; i++) {
       do_something(i);
    }
}
