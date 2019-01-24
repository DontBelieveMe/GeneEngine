project (Gene2)

set(CurrentDir ${CMAKE_CURRENT_SOURCE_DIR})

add_subdirectory(${CurrentDir}/ThirdParty)

add_subdirectory(${CurrentDir}/Engine/Include/Gene2)
add_subdirectory(${CurrentDir}/Engine/Source)

# Autogenerate .Lib.hpp files that include all the needed header files for
# Each global includes.
# How something is decided to be a module is NOT GOOD (read #todo (bwilks) -> fix)
# As it is just based off the filename.
# Bit it appears to work for small dependencys.
# May need to revist when we have bigger dependencies such as FreeType.
# #todo (bwilks) -> fix
foreach(i ${ThirdPartyGlobalIncludes})
	get_filename_component(ModuleName ${i} NAME_WE)
	set(CMAKE_CONFIGURABLE_FILE_CONTENT )
	file(RELATIVE_PATH RelDir "${CurrentDir}/Engine/Include" ${i})
	set(CMAKE_CONFIGURABLE_FILE_CONTENT "${CMAKE_CONFIGURABLE_FILE_CONTENT}\n#include <${RelDir}>")
	set(InputFile ${CurrentDir}/Tools/CMake/Dep.In.hpp)
	set(OutputHeaderFile ${CurrentDir}/Engine/Include/Gene2/Lib/${ModuleName}.Lib.hpp)
	configure_file(${InputFile} ${OutputHeaderFile} @ONLY)
	list(APPEND EngineHeaders ${OutputHeaderFile})
	unset(CMAKE_CONFIGURABLE_FILE_CONTENT)
endforeach()

add_library(${PROJECT_NAME} ${EngineSource} ${EngineHeaders})
target_link_libraries(${PROJECT_NAME} glfl opengl32.lib)

if(NOT MSVC)
	target_link_libraries(${PROJECT_NAME} m)
endif()


include(${CurrentDir}/Tools/CMake/Common.cmake)

G2_SetSourceGroupsFromFilepaths("${EngineSource}")
G2_SetSourceGroupsFromFilepaths("${EngineHeaders}")

G2_TreatWarningsAsErrors(${PROJECT_NAME})

# Sort out tests.
add_subdirectory(${CurrentDir}/Tests/UnitTests)
