cmake_minimum_required(VERSION 2.8)
find_package(Boost COMPONENTS system REQUIRED)
find_package(PkgConfig)
pkg_check_modules(SSL REQUIRED openssl)

add_definitions(-Wno-ignored-qualifiers)

# set(MIRACAST_SERVICE_INCLUDE_DIRECTORIES
#     ${GLIB2_INCLUDE_DIRS}
#     ${COMMONAPI_INCLUDE_DIRS}
#     ${DBUS1_INCLUDE_DIRS}
#     ${COMMONAPIDBUS_INCLUDE_DIRS}
#     )

set(MIRACAST_SERVICE_LIBRARIES
    ${Boost_SYSTEM_LIBRARY}
    ${SSL_LIBRARIES}
    pthread
)


include_directories(${MIRACAST_SERVICE_INCLUDE_DIRECTORIES})

add_executable(timer1 client.cc)

target_link_libraries(timer1 ${MIRACAST_SERVICE_LIBRARIES})

