cmake_minimum_required(VERSION 2.8)
find_package(PkgConfig)
pkg_check_modules(GTK REQUIRED gtk+-2.0)
# pkg_check_modules(SSL REQUIRED openssl)


add_definitions(-std=c++11)
add_definitions(-Wno-ignored-qualifiers)

project(demoApp)
include_directories(
    ${GTK_INCLUDE_DIRS}
)

add_executable(${PROJECT_NAME} main.cc)
target_link_libraries(${PROJECT_NAME} ${GTK_LIBRARIES})

