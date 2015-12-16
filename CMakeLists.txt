cmake_minimum_required(VERSION 3.3)
project(cslp)


include_directories(project)
add_subdirectory(project)


set(SOURCE_FILES main.c)
add_executable(cslp ${SOURCE_FILES})