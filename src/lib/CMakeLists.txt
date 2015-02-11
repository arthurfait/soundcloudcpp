cmake_minimum_required(VERSION 2.8)
# find_package(PkgConfig)
# pkg_check_modules(CURL REQUIRED libcurl)
# pkg_check_modules(SSL REQUIRED openssl)

SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall -Werror")

add_subdirectory("support")
add_subdirectory("parser")
add_subdirectory("network")


# set(CURL_CLIENT_LIBRARIES
#     ${CURL_LIBRARIES}
#     ${SSL_LIBRARIES}
# )

# project(curl_client_test)
# add_executable(${PROJECT_NAME} network/curl_client_test.cc network/requestCurl.cc)
# target_link_libraries(${PROJECT_NAME} ${CURL_CLIENT_LIBRARIES})


# project(parsers_test)
# include_directories(
#   ${CMAKE_CURRENT_SOURCE_DIR}/support
#   ${CMAKE_CURRENT_SOURCE_DIR}/
#   )
# add_executable(${PROJECT_NAME} parser/tracksparser_test.cc)
# target_link_libraries(${PROJECT_NAME} support_json parser)


project(soundcloud_client)
add_library(${PROJECT_NAME} STATIC query.cc
                                    client.cc
                                    tracks_request.cc)

target_include_directories(${PROJECT_NAME}
                    PUBLIC
                    ${CMAKE_SOURCE_DIR}/support
                    ${CMAKE_SOURCE_DIR}/)

target_link_libraries(${PROJECT_NAME} parser support_json networkCurl)

project(soundcloud_client_test)
add_executable(${PROJECT_NAME} client_test.cc network/requestCurl.cc)
target_link_libraries(${PROJECT_NAME}  soundcloud_client ${CURL_CLIENT_LIBRARIES})
