add_subdirectory(ast/)
add_subdirectory(parser/)

add_library(frontend SHARED src/driver.cpp)
target_include_directories(frontend PUBLIC include/)
target_link_libraries(frontend ast parser)