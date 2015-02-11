cmake_minimum_required(VERSION 2.8)

SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall -Werror")

add_subdirectory("demo")
add_subdirectory("lib")
add_subdirectory("test")
