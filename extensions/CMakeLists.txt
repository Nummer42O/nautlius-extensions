cmake_minimum_required(VERSION 3.16)

# utility function to add extensions to the assortment
# use like add_subdirectory
function(add_extension EXTENSION_NAME)
  add_subdirectory(${EXTENSION_NAME})

  get_property(SUBDIR_TARGETS
    DIRECTORY ${EXTENSION_NAME}
    PROPERTY BUILDSYSTEM_TARGETS
  )
  message(DEBUG "subdir targets for ${EXTENSION_NAME}: ${SUBDIR_TARGETS}")
  list(APPEND ENABLED_EXTENSIONS "${SUBDIR_TARGETS}")

  set(ENABLED_EXTENSIONS "${ENABLED_EXTENSIONS}" PARENT_SCOPE)
endfunction()


# option to enable/disable all extensions at once
option(ENABLE_ALL_BY_DEFAULT "Enable all extensions by default." ON)
message(DEBUG "ENABLE_ALL_BY_DEFAULT: ${ENABLE_ALL_BY_DEFAULT}")

# option to enable/disable colored logging
option(LOGGING_USE_COLOR "Disable colors in log messages." ON)
message(DEBUG "LOGGING_USE_COLOR: ${LOGGING_USE_COLOR}")
if (${LOGGING_USE_COLOR})
  set(LOGGING_USE_COLOR_MACRO "NELOGGING_USE_COLOR")
endif()

# aquisition of globally required resources
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


add_library(nelogging
  SHARED
    logging.c
)
target_compile_definitions(nelogging
  PUBLIC
    ${LOGGING_USE_COLOR_MACRO}
)

# linking of globally required resources
include_directories(
  ${NAUTILUSEXT_INCLUDE_DIRS}
  ${GTK_INCLUDE_DIRS}
  ${CMAKE_CURRENT_SOURCE_DIR}
)
link_libraries(
  ${NAUTILUSEXT_LIBRARIES}
  ${GTK_LIBRARIES}
  nelogging
)


# inclusion of actual extensions
# add future extensions here
add_extension(open-in-vscode ENABLED_EXTENSIONS)


set(ENABLED_EXTENSIONS "${ENABLED_EXTENSIONS}" PARENT_SCOPE)
