/**
 * Copyright (c) 2017 rxi
 *
 * This library is free software; you can redistribute it and/or modify it
 * under the terms of the MIT license. See LICENSE for details.
 */

#include <dos.h>
#include <time.h>
#include "luaobj.h"
#include "vgm.h"

int l_vgm_load(lua_State *L) {
  const char *filename = luaL_checkstring(L, 1);
  const char *err = VgmLoad(filename);
  if (err)
    luaL_error(L, err);
  return 1;
}

int l_vgm_play(lua_State *L) {
  VgmPlay();
  return 1;
}

int l_vgm_stop(lua_State *L) {
  VgmStop();
  return 1;
}

int luaopen_vgm(lua_State *L) {
  luaL_Reg reg[] = {
      {"VgmLoad", l_vgm_load},
      {"VgmPlay", l_vgm_play},
      {"VgmStop", l_vgm_stop},
      {0, 0},
  };
  luaL_newlib(L, reg);
  return 1;
}
