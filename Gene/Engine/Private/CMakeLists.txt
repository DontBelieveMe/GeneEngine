set(ContentSrc 
    ${SrcDir}/Content/OBJModelLoader.cc
)

set(GraphicsSrc 
    ${SrcDir}/Graphics/Buffer.cc
    ${SrcDir}/Graphics/Color.cc
    ${SrcDir}/Graphics/Font.cc
    ${SrcDir}/Graphics/GLSLShader.cc
    ${SrcDir}/Graphics/Light.cc
    ${SrcDir}/Graphics/Texture2D.cc
    ${SrcDir}/Graphics/VertexArray.cc
    ${SrcDir}/Graphics/Renderer2D.cc
    ${SrcDir}/Graphics/FreeTypeFont.cc
    ${SrcDir}/Graphics/FreeTypeFont.h

    ${SrcDir}/Graphics/Factorys/ShaderFactory.cc
)

set(DebugSrc
    ${SrcDir}/Debug/Logger.cc
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
    ${SrcDir}/Graphics/External/lodepng.cc
    
    ${CMAKE_CURRENT_LIST_DIR}/../../ThirdParty/glfl/pregenerated/glfl.cpp
    
    ${CMAKE_CURRENT_LIST_DIR}/../../ThirdParty/tinyobjloader/tiny_obj_loader.cc
    ${CMAKE_CURRENT_LIST_DIR}/../../ThirdParty/tinyobjloader/tiny_obj_loader.h
)

set(VSSourceFilterName "Source Files")

source_group("${VSSourceFilterName}\\Content"  	  FILES ${ContentSrc})
source_group("${VSSourceFilterName}\\Graphics" 	  FILES ${GraphicsSrc})
source_group("${VSSourceFilterName}\\Input"    	  FILES ${InputSrc})
source_group("${VSSourceFilterName}\\IO" 	  	  FILES ${IOSrc})
source_group("${VSSourceFilterName}\\Math" 	  	  FILES ${MathSrc})
source_group("${VSSourceFilterName}\\Platform" 	  FILES ${PlatformSrc})
source_group("${VSSourceFilterName}\\Third Party" FILES ${ThirdPartySrc})
source_group("${VSSourceFilterName}\\Debug" FILES ${DebugSrc})

set(CommonSource
    ${ContentSrc} 
    ${GraphicsSrc}
    ${InputSrc}
    ${IOSrc}
    ${MathSrc}
    ${PlatformSrc}
    ${ThirdPartySrc}
    ${DebugSrc}
)
