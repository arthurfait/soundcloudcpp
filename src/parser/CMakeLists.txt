cmake_minimum_required(VERSION 2.8)

project(parser)
include_directories(${CMAKE_SOURCE_DIR}/support
                    ${CMAKE_SOURCE_DIR}/)
add_library(${PROJECT_NAME} STATIC parser.cc)
