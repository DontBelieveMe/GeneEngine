set(CurrentDir ${CMAKE_CURRENT_SOURCE_DIR})

add_subdirectory(Core/Math)
add_subdirectory(Core/StdLib)

add_subdirectory(Platform)
add_subdirectory(Debug)
add_subdirectory(Graphics)
add_subdirectory(Scene)

add_subdirectory(Input)

set(EngineSource
    ${MathSource}
    ${StdLibSource}
	${DebugSource}
	${PlatformSource}
	${GraphicsSource}
	${SceneSources}
	${InputSource}

    PARENT_SCOPE
)
