cmake_minimum_required(VERSION 3.3)
project(project_run)

set(SOURCE_FILES main.c)
add_executable(project_run ${SOURCE_FILES})

include_directories(project)
add_subdirectory(project)
add_subdirectory(tests)

target_link_libraries(project_run project)