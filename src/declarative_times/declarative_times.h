#pragma once

#include <functional>

namespace declarative_times {

    template <typename CT = unsigned long long>
    struct execute {
        using CountType = CT;
        const CountType n_times;
        const CountType start = 0;
        const CountType step = 1;

        execute(CountType n) : n_times(n) {}

        execute(CountType n_times, CountType start) :
            n_times(n_times),
            start(start)
        {}

        execute(CountType n_times, CountType start, CountType step) :
            n_times(n_times),
            start(start),
            step(step)
        {}

        execute starting_from(CountType start_from)
        {
            return execute<>{ n_times, start_from };
        }

        execute with_step(CountType step_size)
        {
            return execute<>{ n_times, start, step_size };
        }

        CountType total_times() const
        {
            return n_times;
        }

        void operator() (std::function<void()> what)
        {
            for (CountType i = 0; i < n_times; i++)
                what();
        }

        void operator() (std::function<void(CountType)> what)
        {
            for (auto i = 0; i < n_times; i++)
                what(i*step + start);
        }
    };

    inline auto operator"" _times(execute<>::CountType n)
    {
        return execute<>{ n };
    }

    inline auto run(execute<>::CountType n)
    {
        return execute<>{ n };
    }

}
