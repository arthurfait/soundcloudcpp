cmake_minimum_required(VERSION 2.8)

project(soundcloud_client)
add_definitions(-std=c++11)
include_directories(${CMAKE_SOURCE_DIR}/support
                    ${CMAKE_SOURCE_DIR}/)
add_library(${PROJECT_NAME} STATIC query.cc
                                    client.cc
                                    tracks_request.cc)

target_include_directories(${PROJECT_NAME}
                    PUBLIC
                    ${CMAKE_SOURCE_DIR}/support
                    ${CMAKE_SOURCE_DIR}/)

target_link_libraries(${PROJECT_NAME} parser support_json)