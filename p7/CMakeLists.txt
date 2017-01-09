cmake_minimum_required(VERSION 3.6)
project(p7)

set(CMAKE_C_STANDARD 11)

set(SOURCE_FILES e1.c e2.c)
add_executable(p7 ${SOURCE_FILES})
target_link_libraries(p7 m)