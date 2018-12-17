add_subdirectory(Core/Math)
add_subdirectory(Core/StdLib)
add_subdirectory(Platform)

set(EngineHeaders 
    ${MathHeaders}
    ${StdLibHeaders}
	${PlatformHeaders}
    
    PARENT_SCOPE
)
