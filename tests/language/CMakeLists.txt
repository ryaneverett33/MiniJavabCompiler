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
set_property(DIRECTORY APPEND PROPERTY CMAKE_CONFIGURE_DEPENDS ${CMAKE_SOURCE_DIR}/src/Instructions.td)

add_executable(language-tests
    common.cpp
    ${TEST_SUITES})
target_link_libraries(language-tests GTest::gtest_main frontend)

foreach (test_directory IN LISTS TEST_DIRECTORIES)
    add_custom_target(copy_${test_directory} ALL
                    # remove the old directory if it exists
                    COMMAND ${CMAKE_COMMAND} -E rm -rf ${CMAKE_CURRENT_BINARY_DIR}/${test_directory}
                    # copy new directory
                    COMMAND ${CMAKE_COMMAND} -E copy_directory
                            ${CMAKE_CURRENT_SOURCE_DIR}/${test_directory}
                            ${CMAKE_CURRENT_BINARY_DIR}/${test_directory}
                    COMMENT "Copying ${test_directory} test data")
endforeach()

include(GoogleTest)
gtest_discover_tests(language-tests)