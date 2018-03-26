project(FreeType)

set(FTRoot ${CMAKE_CURRENT_LIST_DIR}/src)

include_directories(${CMAKE_CURRENT_LIST_DIR}/include)
include_directories(${CMAKE_CURRENT_LIST_DIR}/devel)

set(FreeTypeSource
    ${FTRoot}/base/ftbase.c
    ${FTRoot}/base/ftbbox.c
    ${FTRoot}/base/ftbitmap.c
    ${FTRoot}/base/ftdebug.c
    ${FTRoot}/base/ftfstype.c
    ${FTRoot}/base/ftgasp.c
    ${FTRoot}/base/ftglyph.c
    ${FTRoot}/base/ftgxval.c
    ${FTRoot}/base/ftinit.c
    ${FTRoot}/base/ftlcdfil.c
    ${FTRoot}/base/ftmm.c
    ${FTRoot}/base/ftotval.c
    ${FTRoot}/base/ftpatent.c
    ${FTRoot}/base/ftpfr.c
    ${FTRoot}/base/ftstroke.c
    ${FTRoot}/base/ftsynth.c
    ${FTRoot}/base/ftsystem.c
    ${FTRoot}/base/fttype1.c
    ${FTRoot}/base/ftwinfnt.c
    ${FTRoot}/base/ftxf86.c
    
    ${FTRoot}/autofit/autofit.c
    ${FTRoot}/bdf/bdf.c
    ${FTRoot}/cache/ftcache.c
    ${FTRoot}/cff/cff.c
    ${FTRoot}/cid/type1cid.c
    ${FTRoot}/gzip/ftgzip.c
    ${FTRoot}/lzw/ftlzw.c
    ${FTRoot}/pcf/pcf.c
    ${FTRoot}/pfr/pfr.c
    ${FTRoot}/psaux/psaux.c
    ${FTRoot}/pshinter/pshinter.c
    ${FTRoot}/psnames/psmodule.c
    ${FTRoot}/raster/raster.c
    ${FTRoot}/sfnt/sfnt.c
    ${FTRoot}/smooth/smooth.c
    ${FTRoot}/truetype/truetype.c
    ${FTRoot}/type1/type1.c
    ${FTRoot}/type42/type42.c
    ${FTRoot}/winfonts/winfnt.c
)

add_definitions(-DFT2_BUILD_LIBRARY)

if(WIN32)
    add_definitions(-D_CRT_SECURE_NO_WARNINGS)
    add_definitions(-D_CRT_SECURE_NO_DEPRECATE)
endif()
if(ANDROID)
    add_library(FreeType OBJECT ${FreeTypeSource})
else()
    add_library(FreeType STATIC ${FreeTypeSource})
endif()

# Set the Visual Studio project filter.
set_property(TARGET FreeType PROPERTY FOLDER "Dependencies")
