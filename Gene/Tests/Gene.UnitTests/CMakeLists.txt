project(GeneEngine.UnitTests)

set(SrcDir ${CMAKE_CURRENT_LIST_DIR}/Tests)

include_directories(${CMAKE_CURRENT_LIST_DIR})

set(TestSource
    ${SrcDir}/Math/TestMathFunctions.cc
    ${SrcDir}/Math/TestMatrix4.cc
    ${SrcDir}/Math/TestVector2.cc
    ${SrcDir}/Math/TestVector3.cc

    ${SrcDir}/Graphics/TestColor.cc

    ${SrcDir}/Content/TestObjLoader.cc
)

add_executable(GeneEngine.UnitTests
    ${TestSource}

    ${SrcDir}/CatchMain.cc
)

target_link_libraries(GeneEngine.UnitTests "Gene")
target_link_libraries(GeneEngine.UnitTests "FreeType")

if(UNIX)
    target_link_libraries(GeneEngine.UnitTests "X11")
    target_link_libraries(GeneEngine.UnitTests "GL")
endif()

if(WIN32)
    target_link_libraries(GeneEngine.UnitTests "opengl32.lib")
endif()

# Set Visual Studio project folder.
set_property(TARGET GeneEngine.UnitTests PROPERTY FOLDER "Engine/Tests")
