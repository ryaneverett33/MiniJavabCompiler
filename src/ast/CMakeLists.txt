project(MiniJavabCompiler)
cmake_minimum_required(VERSION 3.12)
set (CMAKE_CXX_STANDARD 20)

set (SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/UnaryExpNode.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/LiteralExpNode.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/BinaryExpNode.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/TypeNode.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/VarDeclNode.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/MethodDeclNode.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/ClassDeclNode.cpp
)

add_library(AST SHARED ${SOURCES})
target_include_directories(AST PUBLIC ${CMAKE_SOURCE_DIR}/src)