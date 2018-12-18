set(CurrentDir ${CMAKE_CURRENT_SOURCE_DIR})

add_subdirectory(Core/Math)
add_subdirectory(Core/StdLib)

add_subdirectory(Debug)

set(EngineSource
    ${MathSource}
    ${StdLibSource}
	${DebugSource}
	
    PARENT_SCOPE
)
