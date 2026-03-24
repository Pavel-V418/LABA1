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
)
add_executable(LABA1_tests
        test/test.c
        int_type.c
        double_type.c
        dynamic_array.c
        operations.c
        types_info.h
)
