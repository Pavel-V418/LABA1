cmake_minimum_required(VERSION 3.16)

project(LABA1 C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

add_executable(LABA1 main.c
        int_type.c
        double_type.c
        dynamic_array.c
        operations.c
        types_info.h
        dyn_array_type.c
        dyn_array_type.h
        dynamic_array_io.c
        dynamic_array_io.h
)
add_executable(LABA1_tests
        test/test.c
        int_type.c
        double_type.c
        dynamic_array.c
        dyn_array_type.c
        operations.c
        types_info.h
)