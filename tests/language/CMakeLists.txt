project(MiniJavabCompiler)
cmake_minimum_required(VERSION 3.14)
set (CMAKE_CXX_STANDARD 20)

add_executable(language-tests
    common.cpp
    hello_world.cpp)
target_link_libraries(language-tests GTest::gtest_main AST parser)

# TODO files don't get updated
file(COPY hello_world/ DESTINATION hello_world/)

include(GoogleTest)
gtest_discover_tests(language-tests)