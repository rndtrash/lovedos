configure_file(config.h.in config.h)

add_subdirectory(embed)
add_subdirectory(lib)

add_executable(love
  audio.c
  audio.h
  event.c
  event.h
  filesystem.c
  filesystem.h
  font.c
  font.h
  image.c
  image.h
  keyboard.c
  keyboard.h
  luaobj.c
  luaobj.h
  main.c
  main.h
  mouse.c
  mouse.h
  package.c
  package.h
  palette.c
  palette.h
  quad.h
  soundblaster.c
  soundblaster.h
  vga.c
  vga.h
  vgm.c
  vgm.h
  modules/l_audio.c
  modules/l_event.c
  modules/l_filesystem.c
  modules/l_font.c
  modules/l_graphics.c
  modules/l_image.c
  modules/l_keyboard.c
  modules/l_love.c
  modules/l_mouse.c
  modules/l_quad.c
  modules/l_source.c
  modules/l_system.c
  modules/l_timer.c
  modules/l_vgm.c)
target_include_directories(love PRIVATE ${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_CURRENT_BINARY_DIR})
target_link_libraries(love
  PRIVATE
    love_embed cmixer dmt lua microtar pctimer stb_image
)

if (LOVE_TTF)
  target_compile_definitions(love PRIVATE -DLOVE_TTF)
  target_link_libraries(love PRIVATE stb_truetype)
endif()

target_link_options(love
  PUBLIC
    LINKER:-Map=love.map
)
