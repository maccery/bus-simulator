cmake_minimum_required(VERSION 3.3)
project(project_run)

<<<<<<< HEAD
set(SOURCE_FILES main.c)
add_executable(project_run ${SOURCE_FILES})

include_directories(project)
add_subdirectory(project)
add_subdirectory(tests)

target_link_libraries(project_run project)
=======
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
set(SOURCE_FILES main.c parser.h parser.c passenger.c passenger.h minibus.c minibus.h request.c request.h simulation.c simulation.h)
add_executable(cslp ${SOURCE_FILES})

add_subdirectory(tests)
>>>>>>> bus capacity can't be greater than 24 seats
