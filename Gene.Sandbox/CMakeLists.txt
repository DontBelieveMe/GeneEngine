project(GeneEngine.Sandbox)

set(SourceDir ${CMAKE_CURRENT_LIST_DIR}/Source)

set(Source 
    ${SourceDir}/Main.cc
)

add_executable(Gene.Sandbox ${Source})

target_link_libraries(Gene.Sandbox "Gene")
target_link_libraries(Gene.Sandbox "FreeType")

if(UNIX)
	target_link_libraries(Gene.Sandbox "X11")
	target_link_libraries(Gene.Sandbox "GL")
endif()

if(WIN32)
	target_link_libraries(Gene.Sandbox "opengl32.lib")
endif()

add_custom_command(TARGET Gene.Sandbox POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E
        copy_directory
            "${CMAKE_CURRENT_SOURCE_DIR}/Data/"
            "${CMAKE_CURRENT_BINARY_DIR}/Data/"
    COMMENT "Copying Data assets directory for Gene.Sandbox target"
)

set_property(TARGET Gene.Sandbox PROPERTY FOLDER "Sandboxes")
