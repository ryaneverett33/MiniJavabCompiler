project(MiniJavabCompiler)
cmake_minimum_required(VERSION 3.14)
set (CMAKE_CXX_STANDARD 20)

set(TEST_SUITES
    test_hello_world.cpp
    test_comments.cpp
    test_statements.cpp
    test_methods.cpp
    test_arrays.cpp
)
set(TEST_DIRECTORIES
    "hello_world"
    comments
    statements
    methods
    arrays)

add_executable(language-tests
    common.cpp
    ${TEST_SUITES})
target_link_libraries(language-tests GTest::gtest_main AST parser)

foreach (test_directory IN LISTS TEST_DIRECTORIES)
    # remove the old directory if it exists
    file(REMOVE_RECURSE ${CMAKE_CURRENT_BINARY_DIR}/${test_directory}/)
    # copy new directory
    file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/${test_directory}/ DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/${test_directory}/)
endforeach()

include(GoogleTest)
gtest_discover_tests(language-tests)