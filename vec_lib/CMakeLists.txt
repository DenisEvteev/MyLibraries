cmake_minimum_required(VERSION 3.14)
project(vec_lib)

set(CMAKE_CXX_STANDARD 14)

set(STRING_LIB "/home/denis/CLionProjects/String_Lib/String.cpp")

add_executable(vec_lib main.cpp vec.h vec_def.hpp ${STRING_LIB} TrackingAllocator.hpp)