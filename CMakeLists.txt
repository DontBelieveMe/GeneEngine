cmake_minimum_required(VERSION 2.6)
project("Gene")
add_definitions(-std=c++14 -g)
file(GLOB_RECURSE Src "Gene/*.cc")
file(GLOB_RECURSE Headers "Gene/*.h")
include_directories("Gene/Engine/Public")
include_directories("Gene/ThirdParty/glfl/pregenerated")
file(GLOB_RECURSE SandboxSrc "Gene.Sandbox/Source/*.cc")
add_library("Gene" SHARED ${Src})
add_executable("Gene.Sandbox" ${SandboxSrc})
target_link_libraries("Gene.Sandbox" "Gene")
target_link_libraries("Gene.Sandbox" "X11")
target_link_libraries("Gene.Sandbox" "GL")
add_custom_command(TARGET Gene.Sandbox PRE_BUILD
    COMMAND rm -r "${CMAKE_BINARY_DIR}/Data")
add_custom_command(TARGET Gene.Sandbox PRE_BUILD
    COMMAND cp -r
    "../Gene.Sandbox/Data" 
    ${CMAKE_BINARY_DIR})
