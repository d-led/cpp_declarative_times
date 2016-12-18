#pragma once

#include <functional>

namespace declarative_times {

    template <class Base, typename CT = unsigned long long>
    struct execute_data {
        using CountType = CT;
        const CountType n_times;
        const CountType start = 0;
        const CountType step = 1;

        execute_data(CountType n) : n_times(n) {}

        execute_data(CountType n_times, CountType start) :
            n_times(n_times),
            start(start)
        {}

        execute_data(CountType n_times, CountType start, CountType step) :
            n_times(n_times),
            start(start),
            step(step)
        {}
    };

    template <typename CT = unsigned long long>
    struct execute final : execute_data <execute<CT>, CT> {
        using execute_data<execute<CT>, CT>::execute_data;

        template <typename Callable>
        void operator() (Callable what)
        {
            for (auto i = 0; i < this->n_times; i++)
                what();
        }
    };

    template <typename CT = unsigned long long>
    struct execute_with_index final : execute_data <execute_with_index<CT>, CT> {
        using execute_data<execute_with_index<CT>, CT>::execute_data;

        template <typename CallableWithIndex>
        void operator() (CallableWithIndex what)
        {
            for (auto i = 0; i < this->n_times; i++)
                what(i*this->step + this->start);
        }

        execute_with_index starting_from(CountType start_from)
        {
            return execute_with_index{ n_times, start_from };
        }

        execute_with_index with_step(CountType step_size)
        {
            return execute_with_index{ n_times, start, step_size };
        }
    };

    inline auto operator"" _times(execute<>::CountType n)
    {
        return execute<>{ n };
    }

    inline auto operator"" _times_with_index(execute<>::CountType n)
    {
        return execute_with_index<>{ n };
    }

    inline auto run(execute<>::CountType n)
    {
        return execute<>{ n };
    }

    inline auto run_with_index(execute<>::CountType n)
    {
        return execute_with_index<>{ n };
    }

}
