cmake_minimum_required(VERSION 3.13)
project(lab_intro)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)
include_directories(cs221util)
include_directories(cs221util/lodepng)

add_executable(lab_intro
        cs221util/lodepng/lodepng.cpp
        cs221util/lodepng/lodepng.h
        cs221util/PNG.cpp
        cs221util/PNG.h
        cs221util/RGB_HSL.h
        cs221util/HSLAPixel.cpp
        cs221util/HSLAPixel.h
        lab_intro.cpp
        lab_intro.h
        main.cpp
        overlay.png
        rosegarden.png)
