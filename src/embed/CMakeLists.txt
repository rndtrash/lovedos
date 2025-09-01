set(EMBED_FILES
    boot.lua
    nogame.lua
)

if(LOVE_TTF)
    list(APPEND EMBED_FILES font.ttf)
else()
    list(APPEND EMBED_FILES font.png)
endif()

list(TRANSFORM EMBED_FILES PREPEND "${CMAKE_CURRENT_SOURCE_DIR}/")

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

    set_source_files_properties(${output_header} PROPERTIES GENERATED TRUE)
    list(APPEND GENERATED_HEADERS ${output_header})
endforeach()

add_library(love_embed STATIC ${GENERATED_HEADERS})
set_target_properties(love_embed PROPERTIES LINKER_LANGUAGE C)
target_include_directories(love_embed PUBLIC ${CMAKE_CURRENT_BINARY_DIR})
