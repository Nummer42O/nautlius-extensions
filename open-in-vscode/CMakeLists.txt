cmake_minimum_required(VERSION 3.16)


option(ENABLE_OPEN_IN_VSCODE
  "Build and install open-in-vscode."
  ${ENABLE_ALL_BY_DEFAULT}
)
message(STATUS "ENABLE_OPEN_IN_VSCODE: ${ENABLE_OPEN_IN_VSCODE}")

if (${ENABLE_OPEN_IN_VSCODE})
  add_library(open-in-vscode SHARED)
  target_include_directories(open-in-vscode PRIVATE src)

  add_subdirectory(src)
endif()
