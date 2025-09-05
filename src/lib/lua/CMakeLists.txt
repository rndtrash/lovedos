project(lua LANGUAGES C)

add_library(lua STATIC
    lapi.c
    lapi.h
    lauxlib.c
    lauxlib.h
    lbaselib.c
    lbitlib.c
    lcode.c
    lcode.h
    lcorolib.c
    lctype.c
    lctype.h
    ldblib.c
    ldebug.c
    ldebug.h
    ldo.c
    ldo.h
    ldump.c
    lfunc.c
    lfunc.h
    lgc.c
    lgc.h
    linit.c
    liolib.c
    llex.c
    llex.h
    llimits.h
    lmathlib.c
    lmem.c
    lmem.h
    loadlib.c
    lobject.c
    lobject.h
    lopcodes.c
    lopcodes.h
    loslib.c
    lparser.c
    lparser.h
    lstate.c
    lstate.h
    lstring.c
    lstring.h
    lstrlib.c
    ltable.c
    ltable.h
    ltablib.c
    ltm.c
    ltm.h
    lua.h
    lua.hpp
    luaconf.h
    lualib.h
    lundump.c
    lundump.h
    lvm.c
    lvm.h
    lzio.c
    lzio.h)
target_include_directories(lua PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

option(
    LUA_LOCALE
    "Implement the os.setlocale function in Lua's standard library. \
Disabling this option shaves off about 5 KiB from the executable's size, but in return makes os.setlocale always return nil."
    ON)
if (LUA_LOCALE)
    target_compile_definitions(lua PRIVATE LUA_LOCALE)
endif()
option(LUA_COMPAT_ALL "Enable all the compatibility flags" ON)
if (LUA_COMPAT_ALL)
    target_compile_definitions(lua PRIVATE LUA_COMPAT_ALL)
endif()