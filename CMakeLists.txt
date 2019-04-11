cmake_minimum_required(VERSION 3.0)
project(Gene2)

if(NOT MSVC)
	add_compile_options(-std=c++11)
endif()

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

include_directories(Gene2/Engine/Include)

add_subdirectory(Gene2)
add_subdirectory(Gene2.Sandbox)
