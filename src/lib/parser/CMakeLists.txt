cmake_minimum_required(VERSION 2.8)

project(parser)
add_definitions(-std=c++11)
add_library(${PROJECT_NAME} STATIC parser.cc)

target_include_directories(${PROJECT_NAME} PUBLIC
                            ${CMAKE_CURRENT_SOURCE_DIR}
                            ${CMAKE_CURRENT_SOURCE_DIR}/..)

target_link_libraries(${PROJECT_NAME} support_json)