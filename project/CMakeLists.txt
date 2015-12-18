set(project_SOURCES main.c parser.h parser.c passenger.c passenger.h minibus.c minibus.h request.c request.h simulation.c simulation.h dijkstra.c dijkstra.h event.c event.h request.h statistics.h statistics.c tests.c tests.h)
add_executable(project ${project_SOURCES})
