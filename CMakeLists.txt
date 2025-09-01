cmake_minimum_required(VERSION 3.23)
project(LoveDOS
    VERSION 0.42.24
    LANGUAGES C
)

option(
    LUA_LOCALE
    "Implement the os.setlocale function in Lua's standard library. \
Disabling this option shaves off about 5 KiB from the executable's size, but in return makes os.setlocale always return nil."
    ON)
option(
    LOVE_TTF
    "Implement vector fonts parser and renderer in LOVE engine. \
Disabling this function might free up to 40 KiB from the executable's size, but all calls to love.graphics.newFont will return nil."
    ON)

if (LUA_LOCALE)
    add_definitions(-DLUA_LOCALE)
endif()
if (LOVE_TTF)
    add_definitions(-DLOVE_TTF)
endif()

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -O2 -Wall -s -Wno-misleading-indentation")

set(SRC_DIR "${CMAKE_SOURCE_DIR}/src")

include_directories(${SRC_DIR} ${CMAKE_CURRENT_BINARY_DIR})

add_compile_definitions(DMT_ABORT_NULL LUA_COMPAT_ALL)

file(GLOB_RECURSE SRC_FILES "${SRC_DIR}/*.c")

add_subdirectory(src)
