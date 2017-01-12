cmake_minimum_required(VERSION 3.6)
project(p10)

set(CMAKE_C_STANDARD 11)

set(SOURCE_FILES main.c common.h common.c exercices.c exercices.h)
add_executable(p10 ${SOURCE_FILES})
target_link_libraries(p10 m)