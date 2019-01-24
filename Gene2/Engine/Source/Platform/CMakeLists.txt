set(CurrentDir ${CMAKE_CURRENT_SOURCE_DIR})

if(WIN32)
	set(PlatformSpecificFiles
		${CurrentDir}/Windows/Win32Window.cpp
	)
endif()

if(UNIX AND NOT APPLE)
	set(PlatformSpecificFiles
		${CurrentDir}/Linux/X11Window.cpp
	)
endif()

set(PlatformSource
	${CurrentDir}/Intrinsics.cpp
	${CurrentDir}/IWindow.cpp
	${PlatformSpecificFiles}
	
	PARENT_SCOPE
)
