project(dmt LANGUAGES C)

add_library(dmt STATIC dmt.c)
target_include_directories(dmt PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

option(DMT_ABORT_NULL "Abort when unable to allocate memory" OFF)
if(DMT_ABORT_NULL)
    target_compile_definitions(dmt PRIVATE DMT_ABORT_NULL)
endif()
