set(CurrentDir ${CMAKE_CURRENT_SOURCE_DIR})

add_subdirectory(Core/Math)
add_subdirectory(Core/StdLib
)
set(EngineSource
    ${MathSource}
    ${StdLibSource}
    PARENT_SCOPE
)
