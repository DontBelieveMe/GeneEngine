add_subdirectory(Core/Math)
add_subdirectory(Core/StdLib)

set(EngineHeaders 
    ${MathHeaders}
    ${StdLibHeaders}
    
    PARENT_SCOPE
)
