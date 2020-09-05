cmake_minimum_required(VERSION 3.13)
project(lab_trees)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(lab_trees
        binarytree.cpp
        binarytree.h
        binarytree_given.cpp
        coloredout.cpp
        coloredout.h
        main.cpp
        printtree.h
        random.h)
