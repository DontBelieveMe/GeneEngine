project(GeneEngine.Core)

set(SrcDir ${CMAKE_CURRENT_LIST_DIR}/Engine/Private)
set(HeaderDir ${CMAKE_CURRENT_LIST_DIR}/Engine/Public)

include(${CMAKE_CURRENT_LIST_DIR}/Engine/Private/CMakeLists.txt)
include(${CMAKE_CURRENT_LIST_DIR}/Engine/Public/CMakeLists.txt)

set(PlatformSrc)

if(UNIX)
	if(ANDROID)
		list(APPEND PlatformSrc
			${SrcDir}/Platform/Android/AInput.cc
			${SrcDir}/Platform/Android/ATime.cc
			${SrcDir}/Platform/Android/AWindow.cc
			${SrcDir}/Platform/Android/AWindow.h
			${SrcDir}/../../ThirdParty/android/android_native_app_glue.c
		)
	else()
		# Traditional desktop linux
		list(APPEND PlatformSrc
			${SrcDir}/Platform/Linux/X11Input.cc
			${SrcDir}/Platform/Linux/X11Time.cc
			${SrcDir}/Platform/Linux/X11Window.cc
			${SrcDir}/Platform/Linux/X11Window.h
		 )
	 endif()
endif()

if(WIN32)
    list(APPEND PlatformSrc
        ${SrcDir}/Platform/Win32/Win32Input.cc
        ${SrcDir}/Platform/Win32/Win32Time.cc
        ${SrcDir}/Platform/Win32/Win32Window.cc
        ${SrcDir}/Platform/Win32/Win32Window.h
    )
endif()

source_group("Source Files\\Platform\\Win32" FILES ${PlatformSrc})

if(ANDROID)
	add_definitions(-DGENE_OS_ANDROID)
endif()

add_library(Gene STATIC ${CommonSource} ${CommonHeaders} ${PlatformSrc})
target_link_libraries(FreeType)

set_property(TARGET Gene PROPERTY FOLDER "Engine")
