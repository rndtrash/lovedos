cmake_minimum_required(VERSION 3.23)
project(LoveDOS
    VERSION 0.42.24
    LANGUAGES C
)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -O2 -Wall -s -Wno-misleading-indentation")

add_subdirectory(src)
