project(pctimer LANGUAGES C)

add_library(pctimer STATIC gccint8.c)
target_include_directories(pctimer PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})