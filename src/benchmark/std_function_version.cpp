#include "times_fixture.h"

#include <functional>

namespace {

    struct execute {
        const unsigned long long count;

        void operator() (std::function<void()> what) {
            for (auto i = 0; i < count; i++)
                what();
        }

        void operator() (std::function<void(unsigned long long)> what) {
            for (auto i = 0; i < count; i++)
                what(i);
        }
    };

    execute operator"" _times(unsigned long long count) {
        return execute{ count };
    }

}

struct StdFunction : TimesVsLoop {};

BENCHMARK_F(StdFunction, Without_Index, 10, 100)
{
    1000000_times([] {
        do_something();
    });
}

BENCHMARK_F(StdFunction, With_Index, 10, 100)
{
    1000000_times([](unsigned long long i) {
        do_something(i);
    });
}
