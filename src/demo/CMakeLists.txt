cmake_minimum_required(VERSION 2.8)
find_package(PkgConfig)
pkg_check_modules(GTK REQUIRED gtk+-3.0)
pkg_check_modules(GSTREAMER010 REQUIRED gstreamer-1.0)


set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
add_definitions(-Wno-ignored-qualifiers)

project(demoApp)
include_directories(
    ${GTK_INCLUDE_DIRS}
    ${GSTREAMER010_INCLUDE_DIRS}
)

add_executable(${PROJECT_NAME} main_window.cc
    player.cc
    log.cc
    main.cc
    )

target_link_libraries(${PROJECT_NAME} ${GTK_LIBRARIES} ${GSTREAMER010_LIBRARIES} soundcloud_client)

