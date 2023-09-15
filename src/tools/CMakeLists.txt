project(MiniJavabCompiler)
cmake_minimum_required(VERSION 3.14)
set (CMAKE_CXX_STANDARD 17)

add_executable(dump-ast dump-ast.cpp)
target_link_libraries(dump-ast ast parser)

add_executable(typecheck typecheck.cpp)
target_link_libraries(typecheck frontend)