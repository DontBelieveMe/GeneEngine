project(GeneEngine.Core)

set(SrcDir ${CMAKE_CURRENT_LIST_DIR}/Engine/Private)
set(HeaderDir ${CMAKE_CURRENT_LIST_DIR}/Engine/Public)

include(${CMAKE_CURRENT_LIST_DIR}/Engine/Private/CMakeLists.txt)
include(${CMAKE_CURRENT_LIST_DIR}/Engine/Public/CMakeLists.txt)

set(PlatformSrc)

if(UNIX)
	if(ANDROID)
		list(APPEND PlatformSrc
			${SrcDir}/Platform/Android/ATime.cc
			${SrcDir}/Platform/Android/AWindow.cc
			${SrcDir}/Platform/Android/AWindow.h
			${SrcDir}/../../ThirdParty/android/android_native_app_glue.c
		)
	else()
		# Traditional desktop linux
		list(APPEND PlatformSrc
			${SrcDir}/Platform/Linux/X11Time.cc
			${SrcDir}/Platform/Linux/X11Window.cc
			${SrcDir}/Platform/Linux/X11Window.h
		 )
	 endif()
endif()

if(WIN32)
    list(APPEND PlatformSrc
        ${SrcDir}/Platform/Win32/Win32Time.cc
        ${SrcDir}/Platform/Win32/Win32Window.cc
        ${SrcDir}/Platform/Win32/Win32Window.h
    )
endif()

source_group("Source Files\\Platform\\Win32" FILES ${PlatformSrc})

include_directories(${CMAKE_CURRENT_LIST_DIR}/../Dependencies/OpenALSoft/include)

set(imgui ${CMAKE_CURRENT_LIST_DIR}/../Dependencies/imgui)

set(imguiSrc
    ${imgui}/imgui.cpp
    ${imgui}/imgui_draw.cpp
    ${imgui}/imgui_impl_opengl3.cpp
    ${imgui}/imgui_impl_win32.cpp
    ${imgui}/imgui_demo.cpp
)

source_group("Source Files\\Third Party\\imgui" FILES ${imguiSrc})
list(APPEND CommonSource ${imguiSrc})

set(imguiHeaders
    ${imgui}/imconfig.h
    ${imgui}/imgui.h
    ${imgui}/imgui_internal.h
    ${imgui}/stb_rect_pack.h
    ${imgui}/stb_textedit.h
    ${imgui}/stb_truetype.h
    ${imgui}/imgui_impl_opengl3.h
    ${imgui}/imgui_impl_win32.h
)

source_group("Header Files\\Third Party\\imgui" FILES ${imguiHeaders})
list(APPEND CommonHeaders ${imguiHeaders})

include_directories(${CMAKE_CURRENT_LIST_DIR}/libroid/include)

if(ANDROID)
	add_definitions(-DGENE_OS_ANDROID)
	add_library(Gene OBJECT ${CommonSource} ${CommonHeaders} ${PlatformSrc})
else()
	add_library(Gene STATIC ${CommonSource} ${CommonHeaders} ${PlatformSrc})
	target_link_libraries(Gene FreeType OpenAL liblua)
endif()

set_property(TARGET Gene PROPERTY FOLDER "Engine")
