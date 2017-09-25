project(GeneEngine.UnitTests)

set(SrcDir ${CMAKE_CURRENT_LIST_DIR}/Tests)

include_directories(${CMAKE_CURRENT_LIST_DIR})

set(TestSource
    ${SrcDir}/Math/TestMathFunctions.cc
    ${SrcDir}/Math/TestMatrix4.cc
    ${SrcDir}/Math/TestVector2.cc
    ${SrcDir}/Math/TestVector3.cc

    ${SrcDir}/Math/CatchMain.cc
)

add_executable(GeneEngine.UnitTests ${TestSource})

target_link_libraries(GeneEngine.UnitTests "Gene")
target_link_libraries(GeneEngine.UnitTests "X11")
target_link_libraries(GeneEngine.UnitTests "GL")
