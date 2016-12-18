include 'premake'

make_solution 'cpp_declarative_times'

includedirs {
    'src/declarative_times',
    'deps/hayai/src',
    'deps/Catch/single_include',
}

--------------------------------------------------------------------
make_console_app('times_benchmark', {
    'src/benchmark/**.*'
})

use_standard('c++14')

run_target_after_build()

--------------------------------------------------------------------
make_console_app('times_test', {
    'src/test/**.*',
    'src/declarative_times/**.*',
})

use_standard('c++14')

run_target_after_build()
