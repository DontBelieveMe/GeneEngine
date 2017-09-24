project(GeneEngine.Core)

set(SrcDir ${CMAKE_CURRENT_LIST_DIR}/Engine/Private)
set(HeaderDir ${CMAKE_CURRENT_LIST_DIR}/Engine/Public)

set(CommonSource
    ${SrcDir}/Content/GeneModel.cc
    ${SrcDir}/Content/OBJModelLoader.cc

    ${SrcDir}/Graphics/External/lodepng.cc
    ${SrcDir}/Graphics/Buffer.cc
    ${SrcDir}/Graphics/Color.cc
    ${SrcDir}/Graphics/Font.cc
    ${SrcDir}/Graphics/GLSLShader.cc
    ${SrcDir}/Graphics/Light.cc
    ${SrcDir}/Graphics/PreBuiltVertices.cc
    ${SrcDir}/Graphics/Texture2D.cc
    ${SrcDir}/Graphics/VertexArray.cc
    
    ${SrcDir}/Input/Keyboard.cc
    ${SrcDir}/Input/Mouse.cc

    ${SrcDir}/IO/File.cc

    ${SrcDir}/Math/Matrix4.cc
    ${SrcDir}/Math/Quaternion.cc
    ${SrcDir}/Math/Vector2.cc
    ${SrcDir}/Math/Vector3.cc

    ${SrcDir}/Platform/GLFLLoad.cc
    ${SrcDir}/Platform/Time.cc
    ${SrcDir}/Platform/Window.cc

    ${SrcDir}/Graphics/External/lodepng.h    
    ${SrcDir}/Graphics/FreetypeGL.h

    ${CMAKE_CURRENT_LIST_DIR}/ThirdParty/glfl/pregenerated/glfl.cc    
)

set(CommonHeaders
    ${HeaderDir}/Content/IModelLoader.h
    ${HeaderDir}/Content/OBJModelLoader.h

    ${HeaderDir}/Graphics/Buffer.h
    ${HeaderDir}/Graphics/Color.h
    ${HeaderDir}/Graphics/Font.h
    ${HeaderDir}/Graphics/GLSLShader.h
    ${HeaderDir}/Graphics/Light.h
    ${HeaderDir}/Graphics/PreBuiltVertices.h
    ${HeaderDir}/Graphics/Texture2D.h
    ${HeaderDir}/Graphics/VertexArray.h

    ${HeaderDir}/Input/Keyboard.h
    ${HeaderDir}/Input/KeyboardState.h
    ${HeaderDir}/Input/Keys.h
    ${HeaderDir}/Input/Mouse.h
    ${HeaderDir}/Input/MouseState.h

    ${HeaderDir}/IO/File.h

    ${HeaderDir}/Math/Functions.h
    ${HeaderDir}/Math/Math.h
    ${HeaderDir}/Math/Matrix4.h
    ${HeaderDir}/Math/Quaternion.h
    ${HeaderDir}/Math/Vector2.h
    ${HeaderDir}/Math/Vector3.h

    ${HeaderDir}/Platform/FreeType.h
    ${HeaderDir}/Platform/GLContext.h
    ${HeaderDir}/Platform/OpenAL.h
    ${HeaderDir}/Platform/OpenGL.h
    ${HeaderDir}/Platform/OS.h
    ${HeaderDir}/Platform/Time.h
    ${HeaderDir}/Platform/Window.h

    ${HeaderDir}/GeneCommon.h
    ${HeaderDir}/GeneUseAll.h
)

set(PlatformSrc)

if(UNIX)
    list(APPEND PlatformSrc
        ${SrcDir}/Platform/Linux/X11Input.cc
        ${SrcDir}/Platform/Linux/X11Time.cc
        ${SrcDir}/Platform/Linux/X11Window.cc
        ${SrcDir}/Platform/Linux/X11Window.h
     )
endif()

if(WIN32)
    list(APPEND PlatformSrc
        ${SrcDir}/Platform/Win32/Win32Input.cc
        ${SrcDir}/Platform/Win32/Win32Time.cc
        ${SrcDir}/Platform/Win32/Win32Window.cc
        ${SrcDir}/Platform/Win32/Win32Window.h
    )
endif()

add_library(Gene SHARED ${CommonSource} ${CommonHeaders} ${PlatformSrc})
