project(MiniJavabCompiler)
cmake_minimum_required(VERSION 3.14)
set (CMAKE_CXX_STANDARD 17)

if (${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
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

BISON_TARGET(Parser parser.yy ${CMAKE_CURRENT_BINARY_DIR}/parser.cpp
             DEFINES_FILE ${CMAKE_CURRENT_BINARY_DIR}/parser.h)
             # COMPILE_FLAGS -Wcounterexamples)
FLEX_TARGET(Tokenizer tokenizer.ll ${CMAKE_CURRENT_BINARY_DIR}/tokenizer.cpp)
ADD_FLEX_BISON_DEPENDENCY(Tokenizer Parser)

add_library(parser SHARED scanner.cpp ${BISON_Parser_OUTPUTS} ${FLEX_Tokenizer_OUTPUTS})
target_include_directories(parser PRIVATE ${CMAKE_CURRENT_BINARY_DIR} ${CMAKE_CURRENT_SOURCE_DIR})

# link against the AST library
target_link_libraries(parser ast)