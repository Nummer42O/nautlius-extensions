cmake_minimum_required(VERSION 3.16)

add_library(open-in-vscode SHARED)
target_include_directories(open-in-vscode PRIVATE src)

add_subdirectory(src)