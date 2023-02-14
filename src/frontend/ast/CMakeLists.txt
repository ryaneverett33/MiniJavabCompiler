project(MiniJavabCompiler)
cmake_minimum_required(VERSION 3.14)
set (CMAKE_CXX_STANDARD 20)

set (SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/UnaryExpNode.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/LiteralExpNode.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/BinaryExpNode.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/TypeNode.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/VarDeclNode.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/MethodDeclNode.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/ClassDeclNode.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/IfStatementNode.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/MethodCallExpNode.cpp
)

add_library(ast SHARED ${SOURCES})
target_include_directories(ast PUBLIC ${CMAKE_SOURCE_DIR}/src)