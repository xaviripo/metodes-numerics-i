cmake_minimum_required(VERSION 3.6)
project(p11)

set(CMAKE_C_STANDARD 11)

set(SOURCE_FILES main.c common.h common.c e1.c e1.h exercices.c exercices.h)
add_executable(p11 ${SOURCE_FILES})