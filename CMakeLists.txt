cmake_minimum_required(VERSION 3.16)
project(nautilus-extensions
  LANGUAGES C
)

find_package(PkgConfig 0.29 REQUIRED)
pkg_check_modules(
  NAUTILUSEXT
  IMPORTED_TARGET
    libnautilus-extension
  REQUIRED
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

add_subdirectory(open-in-vscode)

# TODO: configure?
# TODO: install, uninstall
