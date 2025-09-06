/**
 * Copyright (c) 2025 rndtrash
 *
 * This library is free software; you can redistribute it and/or modify it
 * under the terms of the MIT license. See LICENSE for details.
 */

#include <dos.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include "luaobj.h"

static FILE *printFile = NULL;

static void print_close() {
  if (printFile != NULL && printFile != stdout && printFile != stdin && printFile != stderr) {
    fclose(printFile);
    printFile = NULL;
  }
}

static int l_dos_print(lua_State *L) {
  int n = lua_gettop(L);  /* number of arguments */
  if (printFile == NULL) {
    lua_pop(L, n);
    return 0;
  }

  int i;
  lua_getglobal(L, "tostring");
  for (i=1; i<=n; i++) {
    const char *s;
    size_t l;
    lua_pushvalue(L, -1);  /* function to be called */
    lua_pushvalue(L, i);   /* value to print */
    lua_call(L, 1, 1);
    s = lua_tolstring(L, -1, &l);  /* get result */
    if (s == NULL)
      return luaL_error(L,
         LUA_QL("tostring") " must return a string to " LUA_QL("print"));
    if (i>1) fwrite("\t", sizeof(char), 1, printFile);
    fwrite(s, sizeof(char), l, printFile);
    lua_pop(L, 1);  /* pop result */
  }
  fwrite("\n", sizeof(char), 1, printFile);
  fflush(printFile);
  return 0;
}

int l_dos_setPrintOutput(lua_State *L) {
  if (lua_isnoneornil(L, 1)) {
    print_close();
  } else {
    const char *filename = luaL_checkstring(L, 1);
    printFile = fopen(filename, "w");
    if (printFile == NULL) {
      luaL_error(L, "%s", strerror(errno));
      return 1;
    }
  }
  lua_pushnil(L);
  return 1;
}

static const struct luaL_Reg g_replacements[] = {
  {"print", l_dos_print},
  {NULL, NULL}
};

int luaopen_dos(lua_State *L) {
  // Open the default log file
  printFile = stdout;

  // Close the file on exit
  atexit(print_close);

  // Redefine the default "print" function
  lua_getglobal(L, "_G");
  luaL_setfuncs(L, g_replacements, 0);
  lua_pop(L, 1);

  luaL_Reg reg[] = {
      {"setPrintOutput", l_dos_setPrintOutput},
      {0, 0},
  };
  luaL_newlib(L, reg);
  return 1;
}
