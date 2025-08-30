cmake_minimum_required(VERSION 3.20)
project(lovedos C)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -O2 -Wall -s -Wno-misleading-indentation")

set(SRC_DIR "${CMAKE_SOURCE_DIR}/src")
set(EMBED_DIR "${SRC_DIR}/embed")

include_directories(${SRC_DIR} ${CMAKE_CURRENT_BINARY_DIR})

add_compile_definitions(DMT_ABORT_NULL LUA_COMPAT_ALL)

file(GLOB_RECURSE EMBED_FILES "${EMBED_DIR}/*")

foreach(embed_file ${EMBED_FILES})
    get_filename_component(embed_name ${embed_file} NAME)
    string(REGEX REPLACE "[^a-zA-Z0-9]" "_" embed_var ${embed_name})
    string(TOLOWER ${embed_var} embed_var)

    set(output_header "${CMAKE_CURRENT_BINARY_DIR}/${embed_var}.h")

    add_custom_command(
        OUTPUT ${output_header}
        COMMAND ${CMAKE_COMMAND}
                -DINPUT_FILE=${embed_file}
                -DOUTPUT_FILE=${output_header}
                -P ${CMAKE_SOURCE_DIR}/cmake/make_c_include.cmake
        DEPENDS ${embed_file}
        COMMENT "Embedding: ${embed_file}"
    )

    list(APPEND GENERATED_HEADERS ${output_header})
endforeach()

file(GLOB_RECURSE SRC_FILES "${SRC_DIR}/*.c")

add_executable(love ${SRC_FILES} ${GENERATED_HEADERS})