project(MiniJavabCompiler)
cmake_minimum_required(VERSION 3.14)
set (CMAKE_CXX_STANDARD 17)

add_subdirectory(ast/)
add_subdirectory(parser/)

add_library(frontend SHARED
    Frontend.cpp
    ASTClassTable.cpp
    TypeChecker.cpp)
target_link_libraries(frontend core ast parser)