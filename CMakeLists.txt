cmake_minimum_required(VERSION 3.23)
project(LoveDOS
    VERSION 0.42.24
    LANGUAGES C
)

option(
    LOVE_TTF
    "Implement vector fonts parser and renderer in LOVE engine. \
Disabling this function might free up to 40 KiB from the executable's size, but all calls to love.graphics.newFont will return nil."
    ON)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -O2 -Wall -s -Wno-misleading-indentation")

add_subdirectory(src)
