cmake_minimum_required(VERSION 3.16)


# add per extension option to enable/disable compilation
option(ENABLE_OPEN_IN_VSCODE
  "Build and install open-in-vscode."
  ${ENABLE_ALL_BY_DEFAULT}
)
message(DEBUG "ENABLE_OPEN_IN_VSCODE: ${ENABLE_OPEN_IN_VSCODE}")

if (${ENABLE_OPEN_IN_VSCODE})
  add_library(open-in-vscode
    SHARED
      entrypoint.c
      open-in-vscode.c
      utilities.c
  )
  target_include_directories(open-in-vscode PRIVATE src)
endif()
