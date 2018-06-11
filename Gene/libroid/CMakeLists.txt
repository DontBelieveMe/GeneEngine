project(libroid)

set(src_dir ${CMAKE_CURRENT_LIST_DIR}/source)
set(header_dir ${CMAKE_CURRENT_LIST_DIR}/include/libroid)
include_directories(include)

set(src
    ${src_dir}/JavaObject.cc
    ${src_dir}/Activity.cc
    ${src_dir}/View.cc
    ${src_dir}/Window.cc
)

set(headers
    ${header_dir}/JavaObject.h
    ${header_dir}/Activity.h
    ${header_dir}/JavaObject.h
    ${header_dir}/View.h
    ${header_dir}/JavaEnvironment.h
)

add_library(libroid STATIC ${src} ${headers})