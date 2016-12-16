#include <hayai.hpp>

struct TimesVsLoop : public ::hayai::Fixture{
    static int v;

    static inline void do_something() {
        v = v % 41 + 1;
    }

    static inline void do_something(unsigned long long i) {
        v = (i + v) % 41 + 1;
    }
};
