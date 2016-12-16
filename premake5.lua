include 'premake'

make_solution 'cpp_declarative_times'

includedirs {
    'deps/hayai/src',
}

--------------------------------------------------------------------
make_console_app('times_benchmark', {
    'src/benchmark/**.*'
})

use_standard('c++14')

run_target_after_build()
