cmake_minimum_required(VERSION 3.3)
project(lab_2_2_2)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.c declaration.h implementation.c)
add_executable(lab_2_2_2 ${SOURCE_FILES})