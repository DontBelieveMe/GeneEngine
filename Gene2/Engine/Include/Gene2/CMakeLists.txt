add_subdirectory(Core/Math)
add_subdirectory(Core/StdLib)
add_subdirectory(Core/Utility)

add_subdirectory(Platform)
add_subdirectory(Debug)
add_subdirectory(Input)
add_subdirectory(Graphics)
add_subdirectory(Scene)

set(EngineHeaders 
    ${MathHeaders}
    ${StdLibHeaders}
    ${UtilityHeaders}
	${PlatformHeaders}
	${DebugHeaders}
    ${InputHeaders}
	${GraphicsHeaders}
	${SceneHeaders}

    PARENT_SCOPE
)
