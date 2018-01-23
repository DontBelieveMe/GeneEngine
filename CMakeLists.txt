cmake_minimum_required(VERSION 2.6)
project("GeneEngine")

# This is going to be used in every (sub) project, so its ok to put it here
include_directories(Gene/Engine/Public)
include_directories(${CMAKE_CURRENT_LIST_DIR}/Dependencies/FreeType/include)
include_directories(Gene.GML/Public)

set(CMAKE_SUPPRESS_REGENERATION true)
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

add_subdirectory(Dependencies/FreeType)
add_subdirectory(Gene)
add_subdirectory(Gene.Sandbox)
add_subdirectory(Gene/Tests/Gene.UnitTests)