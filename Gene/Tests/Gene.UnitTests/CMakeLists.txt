project(GeneEngine.UnitTests)

# TODO: Fix test building on all platforms at a later date
if(FALSE)
set(SrcDir ${CMAKE_CURRENT_LIST_DIR}/Tests)

include_directories(${CMAKE_CURRENT_LIST_DIR})

set(CMAKE_MODULE_PATH
    ${CMAKE_CURRENT_LIST_DIR}/../../../Setup/CMake
)

set(TestSource
    ${SrcDir}/Math/TestMathFunctions.cc
    ${SrcDir}/Math/TestMatrix4.cc
    ${SrcDir}/Math/TestVector2.cc
    ${SrcDir}/Math/TestVector3.cc
    ${SrcDir}/Graphics/TestColor.cc
    ${SrcDir}/Content/TestObjLoader.cc
    ${SrcDir}/CatchMain.cc
)

gene_add_target(GeneEngine.UnitTests ${TestSource})
gene_setup_engine_deps(GeneEngine.UnitTests)

# Set Visual Studio project folder.
set_property(TARGET GeneEngine.UnitTests PROPERTY FOLDER "Engine/Tests")

endif()