cmake_minimum_required(VERSION 3.6)
project(p9)

set(CMAKE_C_STANDARD 11)

set(SOURCE_FILES main.c common.c common.h exercices.c exercices.h)
add_executable(p9 ${SOURCE_FILES})
target_link_libraries(p9 m)