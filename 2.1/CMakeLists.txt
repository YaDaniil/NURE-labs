cmake_minimum_required(VERSION 3.3)
project(2_1)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES
    lab_2.1.1/lab_2.1.1/libs/DivTest.CPP
    lab_2.1.1/lab_2.1.1/libs/DivTest.h
    lab_2.1.1/lab_2.1.1/libs/Example_PQ.h
    lab_2.1.1/lab_2.1.1/libs/Primes.cpp
    lab_2.1.1/lab_2.1.1/lab_2.1.1.cpp
    lab_2.1.1/lab_2.1.1/stdafx.cpp
    lab_2.1.1/lab_2.1.1/stdafx.h
    lab_2.1.1/lab_2.1.1/targetver.h
    lab_2.1.2/lab_2.1.2/libs/miracl.h
    lab_2.1.2/lab_2.1.2/libs/mirdef.h
    lab_2.1.2/lab_2.1.2/Source.cpp
    lab_2.1.3/miracl.h
    lab_2.1.3/mirdef.h
    lab_2.1.3/Source.cpp
    lab_2.1.4/lab_2.1.4/libs/miracl.h
    lab_2.1.4/lab_2.1.4/libs/mirdef.h
    lab_2.1.4/lab_2.1.4/main.cpp
    lab_2.1.4v2/lab_2.1.4v2/libs/miracl.h
    lab_2.1.4v2/lab_2.1.4v2/libs/mirdef.h
    lab_2.1.4v2/lab_2.1.4v2/Source.cpp)

add_executable(2_1 ${SOURCE_FILES})