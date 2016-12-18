#include "times_fixture.h"

#include <functional>

namespace {

    // by @kirkshoop
    struct execute {
        const unsigned long long count;

        template<typename F, class Check = decltype((*(F*)nullptr)())>
        void operator() (F what, ...) {
            for (auto i = 0; i < count; i++)
                what();
        }

        template<typename F, class Check = decltype((*(F*)nullptr)(0))>
        void operator() (F what) {
            for (auto i = 0; i < count; i++)
                what(i);
        }
    };

    execute operator"" _times(unsigned long long count) {
        return execute{ count };
    }

}

struct MetaProgram1 : TimesVsLoop {};

BENCHMARK_F(MetaProgram1, Without_Index, 10, 100)
{
    1000000_times([] {
        do_something();
    });
}


BENCHMARK_F(MetaProgram1, With_Index, 10, 100)
{
    1000000_times([](unsigned long long i) {
        do_something(i);
    });
}
