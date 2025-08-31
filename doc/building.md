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
