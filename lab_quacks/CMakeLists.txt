cmake_minimum_required(VERSION 3.13)
project(lab_quacks)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(lab_quacks
        exercises.cpp
        exercises.h
        main.cpp
        quackfun.cpp
        quackfun.h)
