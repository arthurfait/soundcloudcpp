cmake_minimum_required(VERSION 2.8)
find_package(PkgConfig)
pkg_check_modules(CURL REQUIRED libcurl)
pkg_check_modules(SSL REQUIRED openssl)

set(CURL_CLIENT_LIBRARIES
    ${CURL_LIBRARIES}
    ${SSL_LIBRARIES}
)

project(networkCurl)

add_library(${PROJECT_NAME} STATIC requestCurl.cc)
target_include_directories(${PROJECT_NAME}
                    PUBLIC
                    ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(${PROJECT_NAME}   ${CURL_LIBRARIES}
                                        ${SSL_LIBRARIES})