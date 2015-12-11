set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
set(project_SOURCES parser.h parser.c passenger.c passenger.h minibus.c minibus.h request.c request.h simulation.c simulation.h)

add_library(project ${project_SOURCES})