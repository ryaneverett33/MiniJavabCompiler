cmake_minimum_required(VERSION 3.14)
project(MiniJavabCompiler CXX)
set (CMAKE_CXX_STANDARD 17)

# Build Core target
add_library(core SHARED src/core/Type.cpp)

# Build AST target
set (AST_SOURCES
    src/frontend/ast/UnaryExpNode.cpp
    src/frontend/ast/LiteralExpNode.cpp
    src/frontend/ast/BinaryExpNode.cpp
    src/frontend/ast/TypeNode.cpp
    src/frontend/ast/VarDeclNode.cpp
    src/frontend/ast/MethodDeclNode.cpp
    src/frontend/ast/ClassDeclNode.cpp
    src/frontend/ast/IfStatementNode.cpp
    src/frontend/ast/MethodCallExpNode.cpp
)
add_library(ast SHARED ${AST_SOURCES})

# Build flex/bison parser
# TODO: merge this here
add_subdirectory(src/frontend/parser)

# Build frontend target
add_library(frontend SHARED
    src/frontend/Frontend.cpp
    src/frontend/ASTClassTable.cpp
    src/frontend/TypeChecker.cpp)

target_include_directories(ast PUBLIC include/)
target_include_directories(core PUBLIC include/)
target_include_directories(frontend PUBLIC include/)
target_link_libraries(frontend core ast parser)

add_subdirectory(tests/)
add_subdirectory(tools/)