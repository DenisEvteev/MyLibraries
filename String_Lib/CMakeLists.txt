cmake_minimum_required(VERSION 3.14)
project(String_Lib)

set(CMAKE_CXX_STANDARD 14)

set(Exceptions "/home/denis/CLionProjects/MyExceptions/My_Exception.cpp")

add_executable(String_Lib main.cpp String.cpp String.hpp ${Exceptions})