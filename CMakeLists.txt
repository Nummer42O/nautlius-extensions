cmake_minimum_required(VERSION 3.16)
project(nautilus-extensions
  LANGUAGES C
)


function(add_extension EXTENSION_NAME)
  add_subdirectory(${EXTENSION_NAME})

  get_property(SUBDIR_TARGETS
    DIRECTORY ${EXTENSION_NAME}
    PROPERTY BUILDSYSTEM_TARGETS
  )
  message(STATUS "subdir targets for ${EXTENSION_NAME}: ${SUBDIR_TARGETS}")
  list(APPEND ENABLED_EXTENSIONS "${SUBDIR_TARGETS}")

  set(ENABLED_EXTENSIONS "${ENABLED_EXTENSIONS}" PARENT_SCOPE)
endfunction()


option(ENABLE_ALL_BY_DEFAULT "Enable all extensions by default." ON)
message(STATUS "ENABLE_ALL_BY_DEFAULT: ${ENABLE_ALL_BY_DEFAULT}")

find_package(PkgConfig 0.29 REQUIRED)
pkg_check_modules(
  NAUTILUSEXT
  IMPORTED_TARGET
    libnautilus-extension
  REQUIRED
)
pkg_get_variable(
  NAUTILUS_EXTENSION_INSTALL_DIR
  libnautilus-extension
  extensiondir
)
pkg_check_modules(
  GTK
  IMPORTED_TARGET
    gtk4
    glib-2.0
  REQUIRED
)

include_directories(
  ${NAUTILUSEXT_INCLUDE_DIRS}
  ${GTK_INCLUDE_DIRS}
)
link_libraries(
  ${NAUTILUSEXT_LIBRARIES}
  ${GTK_LIBRARIES}
)

add_extension(open-in-vscode ENABLED_EXTENSIONS)

message(STATUS "ENABLED_EXTENSIONS: ${ENABLED_EXTENSIONS}")

install(
  TARGETS "${ENABLED_EXTENSIONS}"
  CONFIGURATIONS Release
  DESTINATION ${NAUTILUS_EXTENSION_INSTALL_DIR}
)

if (NOT TARGET uninstall)
  configure_file(
    ${CMAKE_CURRENT_SOURCE_DIR}/cmake_uninstall.cmake.in
    ${CMAKE_CURRENT_BINARY_DIR}/cmake_uninstall.cmake
    IMMEDIATE @ONLY
  )

  add_custom_target(uninstall
    COMMAND ${CMAKE_COMMAND} -P ${CMAKE_CURRENT_BINARY_DIR}/cmake_uninstall.cmake
  )
endif()
