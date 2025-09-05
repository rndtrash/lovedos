project(cmixer LANGUAGES C)

add_library(cmixer STATIC cmixer.c)
target_include_directories(cmixer PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
