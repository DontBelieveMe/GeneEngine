# Gene Engine 2

Welcome to version 2.0 of Gene Engine - 2.0 as this is the first complete rewrite of the original engine I started when I had no idea of anything. Hopefully this should be slightly better, as I now come better prepared, now having a better idea of how a proper game engine fits together, having learned from many _many_ mistakes. 

## Roadmap

Currently I am focused on getting the functionality of version 2.0 back to where it was with 1.0, including Linux and Android support. This includes:

- New Graphics API (OpenGL based)
  - Including builtin support for ImGui
  - 2D Rendering
    - Font/Text drawing
    - Drawing primitives (rectangles, circles, triangles, complex shapes)
  - Layer based system.
- New Audio API (OpenAL based)
- Scripting with Lua (via LuaJIT, maybe?)
- New Reflection system
  - This time I would like to write it more as a pre-processor based system, using `libclang` or something like that. Kindof like Unreal Engine's `UnrealHeaderTool`.

Features that where not included in the original engine, that I'm looking at

- Game controller input support as well as keyboard/mouse
- Proper assets/resource management
- Some kind of entity component system, whether this will be pure ECS or the Unreal/original Unity hybrid approach is yet to be known, I kinda like features from both :man_shrugging:
- Cool 3D rendering stuff.
  - Rendering with Deferred rendering or Forward+, something like that.
  - Just cool graphics'y stuff. Quite a lot of it is _a little_ advanced, but hey, I can dream.
  - Also support for multiple rendering backends (I'm mainly thinking DirectX11/12 and Vulkan, something like that). Again kind of a pipe dream, but hey, nobody ever got anywhere by not thinking big.

This is not a complete list by any means - it's not even a list of guaranteed features, more like me jotting my thoughts on what I'd _like_ in there.

## Getting Started

#### Requirements

- CMake (version >= 3.0)
- A C++11 compliant compiler
  - Currently only tested with Visual Studio 2017, but I'm planning on getting GCC/Clang working again for Android/Linux as soon as I can.

#### Building

- Navigate into the root directory (on the command line)

- Run `cmake -H. -BBuild` 

- ##### Windows

  - Open up `Gene2.sln` (inside the newly created `Build` folder) in Visual Studio
  - Set `Gene2.Sandbox` as the StartUp project
  - Build & run! :smile:

- ##### Linux

  - Linux not currently supported :disappointed:. Sorry bout' that. It's coming soon though!

- ##### Android

  - Same applies to Android as Linux.

## License

This project is licensed under the MIT License - see the [LICENSE](https://github.com/DontBelieveMe/GeneEngine/blob/Gene2/LICENSE) file for details