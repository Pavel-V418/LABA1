cmake_minimum_required(VERSION 4.1)
project(LABA1 C)

set(CMAKE_C_STANDARD 11)

add_executable(LABA1 main.c
        doubleType.c
        doubleType.h
        dynamicArray.c
        dynamicArray.h
        intType.c
        intType.h
        operations.c
        operations.h
        types_info.h
        test/test.c)
