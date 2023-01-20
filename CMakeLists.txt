project(MiniJavabCompiler)
cmake_minimum_required(VERSION 3.0)

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

BISON_TARGET(Parser src/parser.yy ${CMAKE_CURRENT_BINARY_DIR}/parser.cpp
             DEFINES_FILE ${CMAKE_CURRENT_BINARY_DIR}/parser.h)
FLEX_TARGET(Scanner src/scanner.ll  ${CMAKE_CURRENT_BINARY_DIR}/scanner.cpp)
ADD_FLEX_BISON_DEPENDENCY(Scanner Parser)

add_executable(MiniJavabCompiler src/main.cpp src/driver.cpp ${BISON_Parser_OUTPUTS} ${FLEX_Scanner_OUTPUTS})
target_include_directories(MiniJavabCompiler PRIVATE ${CMAKE_CURRENT_BINARY_DIR} src/include/)