`project(GeneEngine.Sandbox)

set(SourceDir ${CMAKE_CURRENT_LIST_DIR}/Source)

set(Source 
    ${SourceDir}/Main.cc
)

add_executable(Gene.Sandbox ${Source})

target_link_libraries(Gene.Sandbox "Gene")
target_link_libraries(Gene.Sandbox "FreeType")
target_link_libraries(Gene.Sandbox "X11")
target_link_libraries(Gene.Sandbox "GL")

add_custom_command(TARGET Gene.Sandbox POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E
        copy_directory
            "${CMAKE_CURRENT_SOURCE_DIR}/Data/"
            "${CMAKE_CURRENT_BINARY_DIR}/Data/"
    COMMENT "Copying Data assets directory for Gene.Sandbox target"
)
