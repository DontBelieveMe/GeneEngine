set(ContentHeaders 
    ${HeaderDir}/Content/IModelLoader.h
    ${HeaderDir}/Content/OBJModelLoader.h
)

set(GraphicsHeaders 
    ${HeaderDir}/Graphics/Buffer.h
    ${HeaderDir}/Graphics/Color.h
    ${HeaderDir}/Graphics/Font.h
    ${HeaderDir}/Graphics/GLSLShader.h
    ${HeaderDir}/Graphics/Light.h
    ${HeaderDir}/Graphics/Texture2D.h
    ${HeaderDir}/Graphics/VertexArray.h
    ${HeaderDir}/Graphics/Renderer2D.h

    ${HeaderDir}/Graphics/Factorys/ShaderFactory.h
)

set(DebugHeaders
    ${HeaderDir}/Debug/Logger.h
)

set(InputHeaders 
    ${HeaderDir}/Input/Keyboard.h
    ${HeaderDir}/Input/KeyboardState.h
    ${HeaderDir}/Input/Keys.h
    ${HeaderDir}/Input/Mouse.h
    ${HeaderDir}/Input/MouseState.h
)

set(IOHeaders 
    ${HeaderDir}/IO/File.h
)

set(MathHeaders 
    ${HeaderDir}/Math/Functions.h
    ${HeaderDir}/Math/Math.h
    ${HeaderDir}/Math/Matrix4.h
    ${HeaderDir}/Math/Quaternion.h
    ${HeaderDir}/Math/Vector2.h
    ${HeaderDir}/Math/Vector3.h
)

set(PlatformHeaders 
    ${HeaderDir}/Platform/FreeType.h
    ${HeaderDir}/Platform/GLContext.h
    ${HeaderDir}/Platform/OpenAL.h
    ${HeaderDir}/Platform/OpenGL.h
    ${HeaderDir}/Platform/OS.h
    ${HeaderDir}/Platform/Time.h
    ${HeaderDir}/Platform/Window.h
)

set(RootHeaders 
    ${HeaderDir}/GeneCommon.h
    ${HeaderDir}/GeneUseAll.h
)

set(CoreHeaders
    ${HeaderDir}/Core/Array.h
    ${HeaderDir}/Core/String.h
)

set(RuntimeHeaders
    ${HeaderDir}/Runtime/Resources.h
)

set(VSHeaderFilterName "Header Files")

# Set Visual Studio filters.
source_group("${VSHeaderFilterName}\\Content"  FILES ${ContentHeaders})
source_group("${VSHeaderFilterName}\\Graphics" FILES ${GraphicsHeaders})
source_group("${VSHeaderFilterName}\\Input"    FILES ${InputHeaders})
source_group("${VSHeaderFilterName}\\IO"       FILES ${IOHeaders})
source_group("${VSHeaderFilterName}\\Math"     FILES ${MathHeaders})
source_group("${VSHeaderFilterName}\\Platform" FILES ${PlatformHeaders})
source_group("${VSHeaderFilterName}"           FILES ${RootHeaders})
source_group("${VSHeaderFilterName}\\Debug"    FILES ${DebugHeaders})
source_group("${VSHeaderFilterName}\\Core"     FILES ${CoreHeaders})
source_group("${VSHeaderFilterName}\\Runtime"     FILES ${RuntimeHeaders})

set(CommonHeaders
    ${ContentHeaders} 
    ${GraphicsHeaders}
    ${InputHeaders}
    ${IOHeaders}
    ${MathHeaders}
    ${PlatformHeaders}
    ${DebugHeaders}
    ${RootHeaders}
    ${CoreHeaders}
    ${RuntimeHeaders}
)
