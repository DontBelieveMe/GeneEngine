set(CurrentDir ${CMAKE_CURRENT_SOURCE_DIR})

if(WIN32)
	set(PlatformHeaders
		${CurrentDir}/Windows/Win32Window.hpp
	)
endif()

list(APPEND PlatformHeaders
	${CurrentDir}/IWindow.hpp
	${CurrentDir}/Intrinsics.hpp
	${CurrentDir}/PlatformInfo.hpp
	${CurrentDir}/Event.hpp
)

set(PlatformHeaders
	${PlatformHeaders}

	PARENT_SCOPE
)