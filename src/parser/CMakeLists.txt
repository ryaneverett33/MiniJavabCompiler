project(MiniJavabCompiler)
cmake_minimum_required(VERSION 3.12)
set (CMAKE_CXX_STANDARD 20)

if (${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
    # Use homebrew's version of flex/bison
    set(BISON_EXECUTABLE /usr/local/opt/bison/bin/bison)
    set(FLEX_EXECUTABLE /usr/local/opt/flex/bin/flex)
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
FLEX_TARGET(Scanner scanner.ll  ${CMAKE_CURRENT_BINARY_DIR}/scanner.cpp)
ADD_FLEX_BISON_DEPENDENCY(Scanner Parser)

add_executable(MiniJavabCompiler main.cpp driver.cpp ${BISON_Parser_OUTPUTS} ${FLEX_Scanner_OUTPUTS})
target_include_directories(MiniJavabCompiler PRIVATE ${CMAKE_CURRENT_BINARY_DIR} ${CMAKE_CURRENT_SOURCE_DIR})

# link against the AST library
target_link_libraries(MiniJavabCompiler AST)