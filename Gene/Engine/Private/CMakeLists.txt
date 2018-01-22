set(ContentSrc 
    ${SrcDir}/Content/OBJModelLoader.cc
)

set(GraphicsSrc 
	${SrcDir}/Graphics/External/lodepng.cc
    ${SrcDir}/Graphics/Buffer.cc
    ${SrcDir}/Graphics/Color.cc
    ${SrcDir}/Graphics/Font.cc
    ${SrcDir}/Graphics/GLSLShader.cc
    ${SrcDir}/Graphics/Light.cc
    ${SrcDir}/Graphics/Texture2D.cc
    ${SrcDir}/Graphics/VertexArray.cc
    ${SrcDir}/Graphics/Renderer2D.cc

    ${SrcDir}/Graphics/Factorys/ShaderFactory.cc
)

set(InputSrc 
    ${SrcDir}/Input/Keyboard.cc
    ${SrcDir}/Input/Mouse.cc
)

set(IOSrc 
    ${SrcDir}/IO/File.cc
)

set(MathSrc 
	${SrcDir}/Math/Matrix4.cc
    ${SrcDir}/Math/Quaternion.cc
    ${SrcDir}/Math/Vector2.cc
    ${SrcDir}/Math/Vector3.cc
)

set(PlatformSrc 
	${SrcDir}/Platform/GLFLLoad.cc
    ${SrcDir}/Platform/Time.cc
    ${SrcDir}/Platform/Window.cc
)

set(ThirdPartySrc 
	${SrcDir}/Graphics/External/lodepng.h    
    ${SrcDir}/Graphics/FreetypeGL.h

    ${CMAKE_CURRENT_LIST_DIR}/../../ThirdParty/glfl/pregenerated/glfl.cpp
    
    ${CMAKE_CURRENT_LIST_DIR}/../../ThirdParty/tinyobjloader/tiny_obj_loader.cc
    ${CMAKE_CURRENT_LIST_DIR}/../../ThirdParty/tinyobjloader/tiny_obj_loader.h
)

source_group("Source Files\\Content" FILES ${ContentSrc})
source_group("Source Files\\Graphics" FILES ${GraphicsSrc})
source_group("Source Files\\Input" FILES ${InputSrc})
source_group("Source Files\\IO" FILES ${IOSrc})
source_group("Source Files\\Math" FILES ${MathSrc})
source_group("Source Files\\Platform" FILES ${PlatformSrc})
source_group("Source Files\\Third Party" FILES ${ThirdPartySrc})

set(CommonSource
    ${ContentSrc} ${GraphicsSrc} ${InputSrc} ${IOSrc} ${MathSrc} ${PlatformSrc} ${ThirdPartySrc}
)