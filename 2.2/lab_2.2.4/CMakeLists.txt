cmake_minimum_required(VERSION 3.3)
project(lab_2_2_4)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp Integer.cpp Integer.h)
add_executable(lab_2_2_4 ${SOURCE_FILES})