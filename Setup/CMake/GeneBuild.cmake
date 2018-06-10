macro(gene_add_target PROJECT_NAME SOURCE)
	include_directories(${CMAKE_MODULE_PATH}/../../Gene/libroid/include)
	if(ANDROID)
		add_library(${PROJECT_NAME} SHARED ${SOURCE}
			$<TARGET_OBJECTS:Gene>
			$<TARGET_OBJECTS:FreeType>
		)
	else()
		include_directories(${CMAKE_MODULE_PATH}/../../Dependencies/OpenALSoft/include)
		
		message(${SOURCE})
		add_executable(${PROJECT_NAME} ${SOURCE})
		target_link_libraries(${PROJECT_NAME} "Gene")
		target_link_libraries(${PROJECT_NAME} "FreeType")
		target_link_libraries(${PROJECT_NAME} "OpenAL")
	endif()
endmacro()

macro(gene_setup_engine_deps PROJECT_NAME)
	if(UNIX)
		if(ANDROID)
			target_link_libraries(${PROJECT_NAME} android log EGL GLESv3 libroid)
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
