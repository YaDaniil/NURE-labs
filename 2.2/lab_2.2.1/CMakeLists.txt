cmake_minimum_required(VERSION 3.3)
project(lab_2_2_1)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES
    lab_2.2.1/Header.h
    lab_2.2.1/main.cpp
    lab_2.2.1/Source.cpp)

add_executable(lab_2_2_1 ${SOURCE_FILES})