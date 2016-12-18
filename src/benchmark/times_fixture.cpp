#include "times_fixture.h"

int TimesVsLoop::v = 0;

struct LoopBaseline : TimesVsLoop {};

BENCHMARK_F(LoopBaseline, With_Index, 10, 100)
{
    for (auto i = 0; i < 1000000; i++) {
        do_something(i);
    }
}

BENCHMARK_F(LoopBaseline, Without_Index, 10, 100)
{
    for (auto i = 0; i < 1000000; i++) {
        do_something();
    }
}
