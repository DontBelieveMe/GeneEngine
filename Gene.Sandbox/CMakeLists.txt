project(GeneEngine.Sandbox)

set(SourceDir ${CMAKE_CURRENT_LIST_DIR}/Source)

set(CMAKE_MODULE_PATH
	${CMAKE_CURRENT_LIST_DIR}/../Setup/CMake
)

include(GeneBuild)

set(Source 
    ${SourceDir}/Main.cc
)

gene_add_target(Gene.Sandbox ${Source})
gene_setup_engine_deps(Gene.Sandbox)

add_definitions(-DASSETS_DIRECTORY="${CMAKE_CURRENT_SOURCE_DIR}/Data/" -DASSETS_OUT_DIRECTORY="${CMAKE_CURRENT_BINARY_DIR}/Data/")

add_custom_command(TARGET Gene.Sandbox POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E
        copy_directory
            "${CMAKE_CURRENT_SOURCE_DIR}/Data/"
            "${CMAKE_CURRENT_BINARY_DIR}/Data/"
)

set_property(TARGET Gene.Sandbox PROPERTY FOLDER "Sandboxes")
