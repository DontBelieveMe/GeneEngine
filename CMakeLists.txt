cmake_minimum_required(VERSION 3.1)
project("GeneEngine")

set(CMAKE_CXX_STANDARD 11)

# These are going to be used in every (sub) project, so its ok to put it here
include_directories(Gene/Engine/Public)
include_directories(${CMAKE_CURRENT_LIST_DIR}/Dependencies/FreeType/include)

# This suppresses the generation of ZERO_CHECK
set(CMAKE_SUPPRESS_REGENERATION true)

# This allows us to use Visual Studio Folders
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

add_subdirectory(Dependencies/FreeType)
add_subdirectory(Dependencies/luajit)

set_property(TARGET buildvm PROPERTY FOLDER "Dependencies/luajit")
set_property(TARGET liblua PROPERTY FOLDER "Dependencies/luajit")
set_property(TARGET luajit PROPERTY FOLDER "Dependencies/luajit")
set_property(TARGET minilua PROPERTY FOLDER "Dependencies/luajit")
set_property(TARGET wluajit PROPERTY FOLDER "Dependencies/luajit")

if(ANDROID)
    add_subdirectory(Gene/libroid)
endif()

if(NOT ANDROID)
	add_subdirectory(Dependencies/OpenALSoft)
	
	set_property(TARGET OpenAL PROPERTY FOLDER "Dependencies/OpenAL")
	set_property(TARGET native-tools PROPERTY FOLDER "Dependencies/OpenAL")
	set_property(TARGET common PROPERTY FOLDER "Dependencies/OpenAL")
	set_property(TARGET alrecord PROPERTY FOLDER "Dependencies/OpenAL")

	if(TARGET alsoft-config)
	    set_property(TARGET alsoft-config PROPERTY FOLDER "Dependencies/OpenAL")
	endif()
    
	set_property(TARGET altonegen PROPERTY FOLDER "Dependencies/OpenAL")
	set_property(TARGET makehrtf PROPERTY FOLDER "Dependencies/OpenAL")
	set_property(TARGET openal-info PROPERTY FOLDER "Dependencies/OpenAL")
	set_property(TARGET build_version PROPERTY FOLDER "Dependencies/OpenAL")
endif()

add_subdirectory(Gene)
add_subdirectory(Gene.Sandbox)
add_subdirectory(Gene/Tests/Gene.UnitTests)
