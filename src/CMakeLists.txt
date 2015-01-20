cmake_minimum_required(VERSION 2.8)
find_package(PkgConfig)
pkg_check_modules(CURL REQUIRED libcurl)
pkg_check_modules(SSL REQUIRED openssl)

add_subdirectory("support")

add_definitions(-std=c++11)
add_definitions(-Wno-ignored-qualifiers)

# set(MIRACAST_SERVICE_INCLUDE_DIRECTORIES
#     ${GLIB2_INCLUDE_DIRS}
#     ${COMMONAPI_INCLUDE_DIRS}
#     ${DBUS1_INCLUDE_DIRS}
#     ${COMMONAPIDBUS_INCLUDE_DIRS}
#     )

set(CURL_CLIENT_LIBRARIES
    ${CURL_LIBRARIES}
    ${SSL_LIBRARIES}
    support_json
)


project(curl_client_test)
add_executable(${PROJECT_NAME} boostfree/curl_client_test.cc boostfree/requestCurl.cc)
target_link_libraries(${PROJECT_NAME} ${CURL_CLIENT_LIBRARIES})
