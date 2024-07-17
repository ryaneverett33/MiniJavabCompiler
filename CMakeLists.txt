cmake_minimum_required(VERSION 3.14)
project(MiniJavabCompiler CXX)
set(CMAKE_CXX_STANDARD 17)
option(USE_HOMEBREW "fds" OFF)

# Find bison and flex
if (${USE_HOMEBREW})
    # Use homebrew's version of flex/bison
    set(BISON_EXECUTABLE /opt/homebrew/opt/bison/bin/bison)
    set(FLEX_EXECUTABLE /opt/homebrew/opt/flex/bin/flex)
endif()

find_package(BISON 3.4)
find_package(FLEX 2.6)

if (NOT BISON_FOUND)
    MESSAGE(FATAL_ERROR "Couldn't find bison!")
elseif (NOT FLEX_FOUND)
    MESSAGE(FATAL_ERROR "Couldn't find flex!")
endif()

# Build cmdline target
add_library(cmdline STATIC src/cmdline/options.cpp)
target_include_directories(cmdline PUBLIC include/)

set(INSTRUCTIONS
    src/core/ir/Instructions/Alloc.cpp
    src/core/ir/Instructions/Store.cpp
    src/core/ir/Instructions/Load.cpp
    src/core/ir/Instructions/GetPtr.cpp
    src/core/ir/Instructions/Call.cpp
    src/core/ir/Instructions/Mul.cpp
    src/core/ir/Instructions/XOR.cpp
    src/core/ir/Instructions/Add.cpp
    src/core/ir/Instructions/Sub.cpp
    src/core/ir/Instructions/Div.cpp
    src/core/ir/Instructions/Ret.cpp
    src/core/ir/Instructions/Br.cpp
    src/core/ir/Instructions/BrIf.cpp
    src/core/ir/Instructions/Cmp.cpp
    src/core/ir/Instructions/AND.cpp
    src/core/ir/Instructions/OR.cpp)

# Build Core target
add_library(core SHARED
    src/core/ir/Type.cpp
    src/core/ir/AggregateConstant.cpp
    src/core/ir/StructConstant.cpp
    src/core/ir/IntegerConstant.cpp
    src/core/ir/VectorConstant.cpp
    src/core/ir/StringConstant.cpp
    src/core/ir/Constant.cpp
    src/core/ir/PointerConstant.cpp
    src/core/ir/GlobalVariable.cpp
    src/core/ir/Function.cpp
    src/core/ir/IntrinsicFunction.cpp
    src/core/ir/BasicBlock.cpp
    src/core/ir/Module.cpp
    src/core/ir/Immediate.cpp
    src/core/ir/Instruction.cpp
    src/core/ir/IRBuilder.cpp
    src/core/ir/Parameter.cpp
    src/core/ir/ValuePrinter.cpp
    src/core/ir/PrinterImpl.cpp
    ${INSTRUCTIONS})

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
    src/frontend/ast/Type.cpp)
add_library(ast SHARED ${AST_SOURCES})

# Build flex/bison parser
BISON_TARGET(Parser src/frontend/parser/parser.yy ${CMAKE_CURRENT_BINARY_DIR}/parser.cpp
             DEFINES_FILE ${CMAKE_CURRENT_BINARY_DIR}/parser.h)
             # COMPILE_FLAGS -Wcounterexamples)
FLEX_TARGET(Tokenizer src/frontend/parser/tokenizer.ll ${CMAKE_CURRENT_BINARY_DIR}/tokenizer.cpp)
ADD_FLEX_BISON_DEPENDENCY(Tokenizer Parser)

add_library(parser SHARED src/frontend/parser/scanner.cpp ${BISON_Parser_OUTPUTS} ${FLEX_Tokenizer_OUTPUTS})
target_include_directories(parser PUBLIC ${CMAKE_CURRENT_BINARY_DIR} ${CMAKE_BINARY_DIR}/include/)

# link against the AST library
target_link_libraries(parser ast)

# Build frontend target
add_library(frontend SHARED
    src/frontend/Frontend.cpp
    src/frontend/ASTClassTable.cpp
    src/frontend/TypeChecker.cpp
    src/frontend/Converter.cpp
    src/frontend/InstructionLowering.cpp
    src/frontend/ImmediateFolder.cpp)

target_include_directories(ast PUBLIC include/)
target_include_directories(core PUBLIC include/)
target_include_directories(frontend PUBLIC include/)
target_link_libraries(frontend core ast parser)

# Build compiler target
add_executable(mjavabc
    src/compiler/main.cpp)
target_include_directories(mjavabc PUBLIC include/)

target_link_libraries(mjavabc cmdline frontend)

add_subdirectory(tests/)
add_subdirectory(tools/)