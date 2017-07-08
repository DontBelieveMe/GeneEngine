# README #

### What is this repository for? ###

A Multiplatform, custom written OpenGL game engine, designed for ease of use and speed  

Currently supported platforms:  
  - Windows  
  - Linux 
  
Plans for future platforms  
  - Android  
  - Mac  
  - iOS  

Version: (Prealpha) 000

### How do I get set up? ###
#### Windows  
  - Download/Clone the repository
  - Open the Gene.sln in Visual Studio 2017 (other versions may work, but not tested as of writing)
  - Any dependencies should already be setup/packaged within the repository/solution.

#### Linux  
  - Download/Clone the repository
  - Make sure CMake, a C++11 compliant GCC compiler and make is installed. If not install them.  
  - Execute `cmake -H. -BBuild` in the root directory  
  - Enter the `Build` directory and run `make` to build
  - Run `.\Gene.Sandbox` to run the sandbox project

### Contribution guidelines ###

#### Coding Standard
  - Classes and functions/methods are in pascal case (i.e `Render()` or `class Matrix4`)
  - Everything is enclosed in a global namespace `Gene`, with relevant subnamespaces for each 'module' of the engine
  - Local variables and arguments are camelCase (i.e `int xPos = 0;` or `void DoNothing(int offsetOnXAsix);`
  - Subnamespace declarations should be declared on the same line (i.e `namespace Gene { namespace Platform { namspace Win32 {`
  
### Who do I talk to? ###
Me, at the moment (aka @blaclegi)

