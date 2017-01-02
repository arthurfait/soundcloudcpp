cmake_minimum_required(VERSION 2.8)
find_package(PkgConfig)
pkg_check_modules(GTK REQUIRED gtk+-2.0)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

project(soundcloud_plugin)
include_directories(
    ${GTK_INCLUDE_DIRS}
)


add_library(${PROJECT_NAME} SHARED
    soundcloud_widget.cc
    # plugin.cc
    # plugin_entry.c
)

target_link_libraries(${PROJECT_NAME} ${GTK_LIBRARIES} soundcloud_client)
