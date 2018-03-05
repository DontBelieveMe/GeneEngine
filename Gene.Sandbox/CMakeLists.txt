project(GeneEngine.Sandbox)

set(SourceDir ${CMAKE_CURRENT_LIST_DIR}/Source)

set(Source 
    ${SourceDir}/Main.c
)
if(ANDROID)
	add_library(Gene.Sandbox SHARED ${Source})
else()
	add_executable(Gene.Sandbox ${Source})
endif()

target_link_libraries(Gene.Sandbox "Gene")
target_link_libraries(Gene.Sandbox "FreeType")

if(UNIX)
	if(ANDROID)
		target_link_libraries(Gene.Sandbox android log EGL GLESv2)
	else()
		target_link_libraries(Gene.Sandbox "X11")
		target_link_libraries(Gene.Sandbox "GL")
	endif()
endif()

if(WIN32)
	target_link_libraries(Gene.Sandbox "opengl32.lib")
endif()

if(ANDROID)
	add_definitions(-DGENE_OS_ANDROID)
endif()

add_custom_command(TARGET Gene.Sandbox POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E
        copy_directory
            "${CMAKE_CURRENT_SOURCE_DIR}/Data/"
            "${CMAKE_CURRENT_BINARY_DIR}/Data/"
    COMMENT "Copying Data assets directory for Gene.Sandbox target"
)

set_property(TARGET Gene.Sandbox PROPERTY FOLDER "Sandboxes")
