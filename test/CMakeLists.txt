cmake_minimum_required(VERSION 4.1)

add_executable(LABA1_tests
        test.c
        ../dynamicArray.c
        ../operations.c
        ../intType.c
        ../doubleType.c
)

target_include_directories(LABA1_tests PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/..
)