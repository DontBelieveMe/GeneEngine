set(CurrentScope ${CMAKE_CURRENT_LIST_DIR})

set(PlatformSpecificHeaders)

if(WIN32)
	list(APPEND PlatformSpecificHeaders
		${CurrentScope}/Windows/Win32OpenGL3Context.hpp
	)
endif()

if(UNIX AND NOT APPLE)
	list(APPEND PlatformSpecificHeaders
		${CurrentScope}/Linux/X11OpenGL3Context.hpp
	)
endif()

set(GraphicsHeaders
	${CurrentScope}/RenderDevice.hpp
	${CurrentScope}/Buffer.hpp
	${CurrentScope}/IOpenGL3Context.hpp
	${CurrentScope}/OpenGL.hpp
	${CurrentScope}/Shader.hpp
	${CurrentScope}/Color.hpp
	${CurrentScope}/GraphicsResourceAllocator.hpp
	${CurrentScope}/MemoryRef.hpp
	${CurrentScope}/InputLayout.hpp
	${CurrentScope}/ForwardRenderer3D.hpp

	${PlatformSpecificHeaders}

	PARENT_SCOPE
)
