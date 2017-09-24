project(GeneEngine.Sandbox)

set(SourceDir ${CMAKE_CURRENT_LIST_DIR}/Source)

set(Source 
    ${SourceDir}/Main.cc
)

include_directories(${CMAKE_CURRENT_LIST_DIR}/,,.Gene/Engine/Public)

add_executable(Gene.Sandbox ${Source})

target_link_libraries(Gene.Sandbox "Gene")
target_link_libraries(Gene.Sandbox "X11")
target_link_libraries(Gene.Sandbox "GL")
