# Building LoveDOS
Although LoveDOS provides precompiled binaries on the
[releases page](https://github.com/rxi/lovedos/releases), you may still wish to
build the project's source if you want to make changes to the project.


## Requirements
LoveDOS depends on the following being installed before building:
* **CMake 3.23** is required to generate the Makefiles
* **[DJGPP cross compiler](https://github.com/andrewwutw/build-djgpp)** 
  is required to compile the source files


## Building

First, make sure you have DJGPP binaries in the path. More on that in
the [build-djgpp's README](https://github.com/andrewwutw/build-djgpp/?tab=readme-ov-file#using-djgpp-compiler).

To compile you should clone the Git repository or
[download the .zip](https://github.com/rndtrash/lovedos/archive/master.zip) of it.

Once this is done you should open a terminal in the folder with the source code and
execute the following commands:

 1. `cmake -B build --toolchain=DJGPP.cmake` (generates the build files)
 2. `cmake --build build` (will start the compilation process)

There should now be a file named `love.exe` in the `build/` directory

## Customizing

If you want to disable the features that you don't use in order to save up on memory,
this project provides a set of options to customize your build of LoveDOS:

|Name|Description|Default|
|---|---|---|
|LUA_LOCALE|Implement the os.setlocale function in Lua's standard library. Disabling this option shaves off about 5 KiB from the executable's size, but in return makes `os.setlocale` always return `nil`.|ON|
|LOVE_TTF|Implement vector fonts parser and renderer in LOVE engine.<br>Disabling this function might free up to 40 KiB from the executable's size, but all calls to `love.graphics.newFont` will return `nil`.|ON|
|STBI_JPEG|Enable JPEG support for `love.graphics.newImage`. Adds about 20 KiB to the executable's size.|ON|
|STBI_PNG|Enable PNG support for `love.graphics.newImage`. +14 KiB|ON|
|STBI_BMP|Enable BMP support for `love.graphics.newImage`. +6 KiB|ON|
|STBI_PSD|Enable PSD support (composited view only, no extra channels, 8/16 bit-per-channel) for `love.graphics.newImage`. +2 KiB|ON|
|STBI_TGA|Enable TGA support for `love.graphics.newImage`. +5 KiB|ON|
|STBI_GIF|Enable GIF support for `love.graphics.newImage`. +6 KiB|ON|
|STBI_HDR|Enable HDR support for `love.graphics.newImage`. +5 KiB|ON|
|STBI_PIC|Enable PIC support for `love.graphics.newImage`. +4 LoB|ON|
|STBI_PNM|Enable PNM (.PPM and .PGM) support for `love.graphics.newImage`. +2 KiB|ON|

To use these flags, add them to the end of the first command like this: `-Dname=ON/OFF`. For example, the following command disables PSD and enables TTF:

```
cmake -B build --toolchain=DJGPP.cmake -DSTBI_PSD=OFF -DLOVE_TTF=ON
```

LoveDOS also offers an all-in-one flag called `LOVEDOS_MINI`, which disables a lot of stuff when turned on.
More specifically, it turns off `LUA_LOCALE`, `LOVE_TTF`, and leaves PNG and GIF as the only supported image formats.

Don't forget to clean your `build` folder after changing the build flags!
