macro(gene_add_target PROJECT_NAME SOURCE)
	if(ANDROID)
		add_library(${PROJECT_NAME} SHARED ${SOURCE}
			$<TARGET_OBJECTS:Gene>
			$<TARGET_OBJECTS:FreeType>
		)
	else()
		add_executable(${PROJECT_NAME} ${SOURCE})
		target_link_libraries(${PROJECT_NAME} "Gene")
		target_link_libraries(${PROJECT_NAME} "FreeType")
	endif()
endmacro()

macro(gene_setup_engine_deps PROJECT_NAME)
	if(UNIX)
		if(ANDROID)
			target_link_libraries(${PROJECT_NAME} android log EGL GLESv1_CM)
		else()
			target_link_libraries(${PROJECT_NAME} "X11" "GL")
		endif()
	endif()

	if(WIN32)
		target_link_libraries(${PROJECT_NAME} "opengl32.lib")
	endif()

	if(ANDROID)
		add_definitions(-DGENE_OS_ANDROID)
	endif()
endmacro()