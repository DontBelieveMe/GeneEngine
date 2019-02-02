project(Gene2.Sandbox)

set(Source
    Main.cpp
)

add_executable(${PROJECT_NAME} ${Source})
target_link_libraries(${PROJECT_NAME} Gene2)

# Assets loading

set(AssetsPath ${CMAKE_CURRENT_SOURCE_DIR}/Assets)
file(GLOB AssetShaders ${AssetsPath}/*.shader)

add_custom_target(AssetsTarget
                   COMMAND ${CMAKE_COMMAND} -E copy_directory
				   ${AssetsPath} ${CMAKE_CURRENT_BINARY_DIR}/Assets
		   SOURCES ${AssetShaders}
)
source_group("Shaders" FILES ${AssetsShaders})
add_dependencies(${PROJECT_NAME} AssetsTarget)

set_target_properties(AssetsTarget Gene2.Sandbox PROPERTIES FOLDER "Sandbox")
