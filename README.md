# Gene Engine 2

Welcome to version 2.0 of Gene Engine - 2.0 as this is the first complete rewrite of the original engine I started when I had no idea of anything. Hopefully this should be slightly better, as I now come better prepared, now having a better idea of how a proper game engine fits together, having learned from many _many_ mistakes. 

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