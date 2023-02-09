project(MiniJavabCompiler)
cmake_minimum_required(VERSION 3.12)
set (CMAKE_CXX_STANDARD 20)

add_executable(dump-ast dump-ast.cpp)
target_link_libraries(dump-ast AST parser)