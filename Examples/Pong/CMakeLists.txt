cmake_minimum_required(VERSION 3.1)
set(ProjectName Pong)

project(${ProjectName})

set(GeneLibDir ${CMAKE_CURRENT_SOURCE_DIR}/../../)
set(CMAKE_MODULE_PATH ${GeneLibDir}/Setup/CMake)
add_subdirectory(${GeneLibDir} LibraryBuild)
include(GeneBuild)

include_directories(${GeneLibDir}/Gene/Engine/Public)
include_directories(${GeneLibDir}/Dependencies/FreeType/include)

# Set your source files here
set(Source
	Source/Main.cc
)
add_definitions(-std=c++11)
gene_add_target(${ProjectName} ${Source})
gene_setup_engine_deps(${ProjectName})

add_custom_command(TARGET ${ProjectName} POST_BUILD 
	COMMAND ${CMAKE_COMMAND} -E 
		copy_directory 
			"${CMAKE_CURRENT_SOURCE_DIR}/Data/" 
			"${CMAKE_CURRENT_BINARY_DIR}/Data/" 
	COMMENT "Copying assets"
)
