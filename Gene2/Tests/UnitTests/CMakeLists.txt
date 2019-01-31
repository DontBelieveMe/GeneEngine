project(Gene2.UnitTests)

set(CurrentDir ${CMAKE_CURRENT_LIST_DIR})
set(ThirdPartyDir ${CurrentDir}/../../ThirdParty)

include_directories(
	${ThirdPartyDir}/Catch2/single_include
)

set(SourceFiles
	${CurrentDir}/Main.cpp
	${CurrentDir}/Test_String.cpp
	${CurrentDir}/Test_GraphicsResourceAllocator.cpp
)

add_executable(${PROJECT_NAME} ${SourceFiles})
target_link_libraries(${PROJECT_NAME} Gene2)