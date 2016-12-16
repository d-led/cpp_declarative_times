#include "times_fixture.h"

#include <functional>

namespace {

    // by @kirkshoop
    struct execute {
        const unsigned long long n;

        template<typename F, class Check = decltype((*(F*)nullptr)())>
        void operator() (F what, ...) {
            for (auto i = 0; i < n; i++)
                what();
        }

        template<typename F, class Check = decltype((*(F*)nullptr)(0))>
        void operator() (F what) {
            for (auto i = 0; i < n; i++)
                what(i);
        }
    };

    execute operator"" _times(unsigned long long n) {
        return execute{ n };
    }

}

struct MetaProgram1_TimesVsLoop : TimesVsLoop {};

BENCHMARK_F(MetaProgram1_TimesVsLoop, Times_Without_Index, 10, 100)
{
    1000000_times([] {
        do_something();
    });
}

BENCHMARK_F(MetaProgram1_TimesVsLoop, Loop_Without_Index, 10, 100)
{
    for (auto i = 0; i < 1000000; i++) {
        do_something();
    }
}

BENCHMARK_F(MetaProgram1_TimesVsLoop, Times_Without_Index_Testing_Sequence_Dependency, 10, 100)
{
    1000000_times([] {
        do_something();
    });
}

BENCHMARK_F(MetaProgram1_TimesVsLoop, Times_With_Index, 10, 100)
{
    1000000_times([](unsigned long long i) {
        do_something(i);
    });
}

BENCHMARK_F(MetaProgram1_TimesVsLoop, Loop_With_Index, 10, 100)
{
    for (auto i = 0; i < 1000000; i++) {
        do_something(i);
    }
}
