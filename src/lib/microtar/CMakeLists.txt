project(microtar LANGUAGES C)

add_library(microtar STATIC microtar.c)
target_include_directories(microtar PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})