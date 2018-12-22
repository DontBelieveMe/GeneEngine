project (Gene2)

set(CurrentDir ${CMAKE_CURRENT_SOURCE_DIR})

add_subdirectory(${CurrentDir}/Engine/Include/Gene2)
add_subdirectory(${CurrentDir}/Engine/Source)

add_library(${PROJECT_NAME} ${EngineSource} ${EngineHeaders})

include(${CurrentDir}/Tools/CMake/Common.cmake)

G2_SetSourceGroupsFromFilepaths("${EngineSource}")
G2_SetSourceGroupsFromFilepaths("${EngineHeaders}")

G2_TreatWarningsAsErrors(${PROJECT_NAME})

# Sort out tests.
add_subdirectory(${CurrentDir}/Tests/UnitTests)
