project(Gene2.Sandbox)

set(Source
    Main.cpp
)

add_executable(${PROJECT_NAME} ${Source})
target_link_libraries(${PROJECT_NAME} Gene2)