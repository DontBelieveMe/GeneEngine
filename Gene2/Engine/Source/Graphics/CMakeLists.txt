set(CurrentDir ${CMAKE_CURRENT_LIST_DIR})

set(PlatformSpecificSource)

if(WIN32)
	list(APPEND PlatformSpecificSource
		${CurrentDir}/Windows/Win32OpenGL3Context.cpp
	)
endif()

if(UNIX AND NOT APPLE)
	list(APPEND PlatformSpecificSource
		${CurrentDir}/Linux/X11OpenGL3Context.cpp
	)
endif()

set(GraphicsSource
	${CurrentDir}/RenderDevice.cpp
	${CurrentDir}/Buffer.cpp
	${CurrentDir}/IOpenGL3Context.cpp
	${CurrentDir}/Shader.cpp
	${CurrentDir}/Color.cpp
	${CurrentDir}/InputLayout.cpp
	${CurrentDir}/ForwardRenderer3D.cpp
	${CurrentDir}/GraphicsResourceAllocator.cpp

	${PlatformSpecificSource}

	PARENT_SCOPE
)
