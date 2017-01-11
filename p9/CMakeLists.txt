cmake_minimum_required(VERSION 3.6)
project(p9)

set(CMAKE_C_STANDARD 11)

set(SOURCE_FILES main.c source.c source.h e1.h e1.c e2.c e2.h e3.c e3.h)
add_executable(p9 ${SOURCE_FILES})
target_link_libraries(p9 m)