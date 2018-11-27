project (Gene2)

set(CurrentDir ${CMAKE_CURRENT_SOURCE_DIR})

add_subdirectory(${CurrentDir}/Engine/Include/Gene2)
add_subdirectory(${CurrentDir}/Engine/Source)
add_library(${PROJECT_NAME} ${EngineSource} ${EngineHeaders})

# https://stackoverflow.com/questions/31966135/cmake-source-group-not-working-correctly-with-hierarchical-project-setup
MACRO(SetSourceGroups SourceFiles)
  foreach(FILE ${SourceFiles}) 
    get_filename_component(ABSOLUTE_PATH "${FILE}" ABSOLUTE)
    get_filename_component(PARENT_DIR "${ABSOLUTE_PATH}" DIRECTORY)
    
    string(REPLACE "${CMAKE_CURRENT_SOURCE_DIR}" "" GROUP "${PARENT_DIR}")
    string(REPLACE "/" "\\" GROUP "${GROUP}")
    message(${FILE})
    if ("${FILE}" MATCHES ".*\\.cpp")
        string(REPLACE "Engine\\Source" "" GROUP "${GROUP}")
        set(GROUP "Source Files${GROUP}")
    elseif("${FILE}" MATCHES ".*\\.hpp")
        string(REPLACE "Engine\\Include\\Gene2" "" GROUP "${GROUP}")
      set(GROUP "Header Files${GROUP}")
    endif()
    source_group("${GROUP}" FILES "${FILE}")
  endforeach()
ENDMACRO(SetSourceGroups)

SetSourceGroups("${EngineSource}")
SetSourceGroups("${EngineHeaders}")