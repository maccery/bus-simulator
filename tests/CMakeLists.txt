<<<<<<< HEAD
project(cslp)

add_subdirectory(lib/googletest)
add_subdirectory(basic_tests)
=======
cmake_minimum_required(VERSION 3.3)

set(SOURCE_FILES mytest.c minunit.h)
add_executable(tests ${SOURCE_FILES})
include_directories(../)
link_libraries(cslp tests)
>>>>>>> bus capacity can't be greater than 24 seats
