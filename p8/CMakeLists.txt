cmake_minimum_required(VERSION 3.6)
project(p8)

set(CMAKE_C_STANDARD 11)

set(SOURCE_FILES main.c common.c common.h exercices.h exercices.c)
add_executable(p8 ${SOURCE_FILES})
target_link_libraries(p8 m)