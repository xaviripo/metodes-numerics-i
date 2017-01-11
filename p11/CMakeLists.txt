cmake_minimum_required(VERSION 3.6)
project(p11)

set(CMAKE_C_STANDARD 11)

set(SOURCE_FILES main.c source.h source.c e1.c e1.h)
add_executable(Practica_11 ${SOURCE_FILES})