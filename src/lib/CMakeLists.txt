cmake_minimum_required(VERSION 2.8)
add_definitions(-fPIC)

add_subdirectory("support")
add_subdirectory("parser")
add_subdirectory("network")



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
                                    tracks_request.cc
                                    # auth.cc
                                    types/user.h
                                    types/track.h)

target_include_directories(${PROJECT_NAME}
                    PUBLIC
                    ${CMAKE_SOURCE_DIR}/support
                    ${CMAKE_SOURCE_DIR}/)

target_link_libraries(${PROJECT_NAME} parser networkCurl)

project(soundcloud_client_test)
add_executable(${PROJECT_NAME} client_test.cc network/requestCurl.cc)
target_link_libraries(${PROJECT_NAME}  soundcloud_client ${CURL_CLIENT_LIBRARIES})
