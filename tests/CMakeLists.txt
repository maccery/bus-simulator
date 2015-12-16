
cmake_minimum_required(VERSION 3.3)

set(SOURCE_FILES mytest.c minunit.h)
add_executable(tests ${SOURCE_FILES})
include_directories(../)
link_libraries(cslp tests)

