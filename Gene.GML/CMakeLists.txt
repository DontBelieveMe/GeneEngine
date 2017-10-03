project(Gene.GML)

set(PrivateDir ${CMAKE_CURRENT_LIST_DIR}/Private)
set(PublicDir ${CMAKE_CURRENT_LIST_DIR}/Public/Gene/GML)

add_definitions(--std=c++17)

set(Sources
    ${PrivateDir}/Parser.cc
    ${PrivateDir}/Interpreter.cc
)

set(Headers
    ${PublicDir}/Interpreter.hpp
    ${PublicDir}/Parser.hpp
    ${PublicDir}/Token.hpp
    ${PublicDir}/TokenTypes.hpp
    ${PublicDir}/AbstractSyntaxTree.hpp
)

add_library(Gene.GML ${Sources} ${Headers})
