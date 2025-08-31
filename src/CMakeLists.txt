configure_file(config.h.in config.h)

add_subdirectory(embed)

add_executable(love ${SRC_FILES})
target_include_directories(love PRIVATE ${CMAKE_CURRENT_BINARY_DIR})
target_link_libraries(love PRIVATE love_embed)

target_link_options(love
  PUBLIC
    LINKER:-Map=love.map
)
