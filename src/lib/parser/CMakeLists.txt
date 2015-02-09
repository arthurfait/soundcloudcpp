cmake_minimum_required(VERSION 2.8)

project(parser)
add_definitions(-std=c++11)
include_directories(${CMAKE_SOURCE_DIR}/support
                    ${CMAKE_SOURCE_DIR}/)
add_library(${PROJECT_NAME} STATIC parser.cc)
