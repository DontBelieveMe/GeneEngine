add_subdirectory(Core/Math)
add_subdirectory(Core/StdLib)
add_subdirectory(Core/Utility)

add_subdirectory(Platform)
add_subdirectory(Debug)
add_subdirectory(Input)

set(EngineHeaders 
    ${MathHeaders}
    ${StdLibHeaders}
    ${UtilityHeaders}
	${PlatformHeaders}
	${DebugHeaders}
    ${InputHeaders}
    
    PARENT_SCOPE
)
