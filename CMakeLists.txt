cmake_minimum_required(VERSION 2.6)
project("Gene")

file(GLOB_RECURSE Src "Gene/*.cc")
file(GLOB_RECURSE Headers "Gene/*.h")

if(WIN32)
    file(GLOB_RECURSE _srcs "Gene/Engine/Private/Platform/Linux/*.cc")
    file(GLOB_RECURSE _headers "Gene/Engine/Private/Platform/Linux/*.h")

    foreach(s in ${_srcs})
        list(REMOVE_ITEM Src "${s}")
    endforeach()

    foreach(s in ${_headers})
        list(REMOVE_ITEM Headers "${s}")
    endforeach()
endif()

if(UNIX)
    file(GLOB_RECURSE _srcs "Gene/Engine/Private/Platform/Win32/*.cc")
    file(GLOB_RECURSE _headers "Gene/Engine/Private/Platform/Win32/*.h")

    foreach(s in ${_srcs})
        list(REMOVE_ITEM Src "${s}")
    endforeach()

    foreach(s in ${_headers})
        list(REMOVE_ITEM Headers "${s}")
    endforeach()

    add_definitions(-std=c++14 -g)
endif()

include_directories("Gene/Engine/Public")
#include_directories("Gene/ThirdParty/glfl/pregenerated")

# Get all the source files for the sandbox project
file(GLOB_RECURSE SandboxSrc "Gene.Sandbox/Source/*.cc")

file(GLOB_RECURSE MinecraftDemoSrc "Demos/MinecraftClone/Source/*.cpp")
file(GLOB_RECURSE MinecraftDemoHeaders "Demos/MinecraftClone/Source/*.h")

# Generate Gene as a shared library and the sandbox project as the 
# executable
add_library("Gene" SHARED ${Src} ${Headers})
add_executable("Gene.Sandbox" ${SandboxSrc})
add_executable("MinecraftClone" ${MinecraftDemoSrc} ${MinecraftDemoHeaders})

# Link the relevant libraries
target_link_libraries("Gene.Sandbox" "Gene")
target_link_libraries("Gene.Sandbox" "X11")
target_link_libraries("Gene.Sandbox" "GL")

target_link_libraries("MinecraftClone" "Gene")
target_link_libraries("MinecraftClone" "X11")
target_link_libraries("MinecraftClone" "GL")

# Copy the data directory to the executable directory
#add_custom_command(TARGET Gene.Sandbox PRE_BUILD
#    COMMAND rm -r -f "${CMAKE_BINARY_DIR}/Data")
#add_custom_command(TARGET Gene.Sandbox PRE_BUILD
#    COMMAND cp -r
#    "../Gene.Sandbox/Data"
#    ${CMAKE_BINARY_DIR})

add_custom_command(TARGET MinecraftClone PRE_BUILD
    COMMAND rm -r -f "${CMAKE_BINARY_DIR}/Data")
add_custom_command(TARGET MinecraftClone PRE_BUILD
    COMMAND cp -r
    "~/Dev/geneengine/Demos/MinecraftClone/Data"
    ${CMAKE_BINARY_DIR})
