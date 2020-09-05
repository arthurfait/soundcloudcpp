project(soundcloud_plugin)

find_package(PkgConfig)
pkg_check_modules(GTK2 REQUIRED gtk+-2.0)
pkg_check_modules(AUDACIOUS REQUIRED audacious)

execute_process(COMMAND ${PKG_CONFIG_EXECUTABLE} "--variable" "plugin_dir" "audacious"
                    OUTPUT_VARIABLE plugin_path
                    OUTPUT_STRIP_TRAILING_WHITESPACE
                    )


add_definitions(" -Wno-deprecated-declarations ")

add_library(${PROJECT_NAME} SHARED
    soundcloud_widget.cc
)


target_include_directories(${PROJECT_NAME} PRIVATE ${GTK2_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME} ${GTK2_LIBRARIES} ${AUDACIOUS_LIBRARIES} soundcloud_client)

message(STATUS "Audacious plugins path: ${plugin_path}")
install(TARGETS ${PROJECT_NAME} DESTINATION "${plugin_path}/General")