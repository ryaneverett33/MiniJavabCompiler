project(MiniJavabCompiler)
cmake_minimum_required(VERSION 3.14)
set (CMAKE_CXX_STANDARD 17)

add_library(harness STATIC
    src/harness.cpp)
target_link_libraries(harness GTest::gtest_main frontend)
target_include_directories(harness PUBLIC include/)