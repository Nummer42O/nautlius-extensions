cmake_minimum_required(VERSION 3.16)
project(nautilus-extensions
  LANGUAGES C
)

set(ENABLED_EXTENSIONS "")

add_subdirectory(extensions)

message(NOTICE "ENABLED_EXTENSIONS: ${ENABLED_EXTENSIONS}")


# make install target for release builds
install(
  TARGETS "${ENABLED_EXTENSIONS}"
  CONFIGURATIONS Release
  DESTINATION ${NAUTILUS_EXTENSION_INSTALL_DIR}
)

# make uninstall target
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
