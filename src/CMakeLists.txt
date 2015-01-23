cmake_minimum_required(VERSION 2.8)
find_package(PkgConfig)
pkg_check_modules(CURL REQUIRED libcurl)
pkg_check_modules(SSL REQUIRED openssl)

add_subdirectory("support")

add_definitions(-std=c++11)
add_definitions(-Wno-ignored-qualifiers)


set(CURL_CLIENT_LIBRARIES
    ${CURL_LIBRARIES}
    ${SSL_LIBRARIES}
    support_json
)

project(curl_client_test)
add_executable(${PROJECT_NAME} network/curl_client_test.cc network/requestCurl.cc)
target_link_libraries(${PROJECT_NAME} ${CURL_CLIENT_LIBRARIES})


project(parsers_test)
include_directories(
  ${CMAKE_CURRENT_SOURCE_DIR}/support
  ${CMAKE_CURRENT_SOURCE_DIR}/
  )
add_executable(${PROJECT_NAME} parsers/tracksparser_test.cc)
target_link_libraries(${PROJECT_NAME} support_json)
