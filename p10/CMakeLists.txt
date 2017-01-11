cmake_minimum_required(VERSION 3.6)
project(p10)

set(CMAKE_C_STANDARD 11)

set(SOURCE_FILES main.c e1.c e1.h source.h source.c e2.h e2.c)
add_executable(p10 ${SOURCE_FILES})
target_link_libraries(p10 m)