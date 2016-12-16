Blog: [C++ version of ruby’s Integer::times via user-defined literals](https://ledentsov.de/2016/12/10/cpp-version-ruby-42-times-via-user-defined-literals/)

Benchmarks: [![Build Status](https://travis-ci.org/d-led/cpp_declarative_times.svg?branch=master)](https://travis-ci.org/d-led/cpp_declarative_times)

```cpp
42_times([]{
    do_something();
});
```