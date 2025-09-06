# LoveDOS Config File

The LoveDOS configuration can be defined in a `conf.lua` file, placed in the root of the game folder next to `main.lua`.

It works the same as [conf.lua in LÖVE](https://love2d.org/wiki/Config_Files): one needs to redefine
a method called `love.conf(t)` in `conf.lua` and only in this module. The `t` table in arguments
contains default configuration that could be manipulated within the aforementioned function.
Changes to the configuration are applied after the function returns.

## Properties

### t.dos

A namespace for LoveDOS-specific settings.

##### t.dos.console

A string or `nil` containing a path to the log file.
More on that in the [API documentation for `love.dos.setPrintOutput(filename)`](api.md#lovedossetprintoutputfilename).

## Example

`conf.lua`:

```lua
function love.conf(t)
    if t.dos then
        t.dos.console = "COM1"
        -- t.dos.console = "c:\\test.log"
    end
end
```
