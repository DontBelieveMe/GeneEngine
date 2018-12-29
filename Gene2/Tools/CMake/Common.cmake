macro(G2_TreatWarningsAsErrors target)
    if(MSVC)
        message(${target})
        target_compile_options(${target} PRIVATE /W4 /WX)
    else()
        target_compile_options(${target} PRIVATE -Wall -Wextra -pedantic -Werror)
    endif()
endmacro()

# https://stackoverflow.com/questions/31966135/cmake-source-group-not-working-correctly-with-hierarchical-project-setup
macro(G2_SetSourceGroupsFromFilepaths sourceFiles)
    foreach(file ${sourceFiles}) 
        get_filename_component(ABSOLUTE_PATH "${file}" ABSOLUTE)
        get_filename_component(PARENT_DIR "${ABSOLUTE_PATH}" DIRECTORY)

        string(REPLACE "${CMAKE_CURRENT_SOURCE_DIR}" "" GROUP "${PARENT_DIR}")
        string(REPLACE "/" "\\" GROUP "${GROUP}")

        if ("${file}" MATCHES ".*\\.cpp")
            string(REPLACE "Engine\\Source" "" GROUP "${GROUP}")
            set(GROUP "Source Files${GROUP}")
        elseif("${file}" MATCHES ".*\\.hpp")
            string(REPLACE "Engine\\Include\\Gene2" "" GROUP "${GROUP}")
            set(GROUP "Header Files${GROUP}")
        endif()

        source_group("${GROUP}" FILES "${file}")
    endforeach()
endmacro()