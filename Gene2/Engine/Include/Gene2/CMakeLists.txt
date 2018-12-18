add_subdirectory(Core/Math)
add_subdirectory(Core/StdLib)
add_subdirectory(Core/Utility)

add_subdirectory(Platform)
add_subdirectory(Debug)

set(EngineHeaders 
    ${MathHeaders}
    ${StdLibHeaders}
	${PlatformHeaders}
	${DebugHeaders}
    ${UtilityHeaders}
    PARENT_SCOPE
)
