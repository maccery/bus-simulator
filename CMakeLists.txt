cmake_minimum_required(VERSION 3.3)
project(cslp)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
set(SOURCE_FILES main.c parser.h parser.c passenger.c passenger.h minibus.c minibus.h request.c request.h stop.c stop.h)
add_executable(cslp ${SOURCE_FILES})