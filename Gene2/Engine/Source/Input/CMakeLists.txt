set(CurrentDir ${CMAKE_CURRENT_SOURCE_DIR})

if(WIN32)
	set(PlatformSpecificFiles
		${CurrentDir}/Windows/Win32Keyboard.cpp
	)
endif()

if(UNIX AND NOT APPLE)
	set(PlatformSpecificFiles
		${CurrentDir}/Linux/X11Keyboard.cpp	
	)
endif()

set(InputSource
	${PlatformSpecificFiles}

	PARENT_SCOPE
)
