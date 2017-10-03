project(Gene.GML.Sandbox)

add_definitions(--std=c++17)

set(Source
    ${CMAKE_CURRENT_LIST_DIR}/Source/Main.cc
)

add_executable(Gene.GML.Sandbox ${Source})
target_link_libraries(Gene.GML.Sandbox Gene.GML)

