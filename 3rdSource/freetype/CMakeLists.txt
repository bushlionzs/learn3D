#Enforce the highest possible version that the current Ubuntu LTS provides
#by default. We want to be sure to have the ability to attach as many things
#to the target as modern cmake code affords us
cmake_minimum_required(VERSION 3.16 FATAL_ERROR)
add_definitions(-DFT2_BUILD_LIBRARY)
add_definitions(-DFT_CONFIG_OPTION_SYSTEM_ZLIB)
add_definitions(-DFT_CONFIG_OPTION_USE_BROTLI)

add_definitions(-D_WIN32)


set(FREETYPE_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR})

file(GLOB  FREETYPE_MODULES_SOURCE 
    "${FREETYPE_SOURCE_DIR}/src/autofit/autofit.c",
	"${FREETYPE_SOURCE_DIR}/src/base/ftbase.c",
	"${FREETYPE_SOURCE_DIR}/src/base/ftbbox.c",
	"${FREETYPE_SOURCE_DIR}/src/base/ftbdf.c",
	"${FREETYPE_SOURCE_DIR}/src/base/ftbitmap.c",
	"${FREETYPE_SOURCE_DIR}/src/base/ftcid.c",
	"${FREETYPE_SOURCE_DIR}/src/base/ftdebug.c",
	"${FREETYPE_SOURCE_DIR}/src/base/ftfstype.c",
	"${FREETYPE_SOURCE_DIR}/src/base/ftgasp.c",
	"${FREETYPE_SOURCE_DIR}/src/base/ftglyph.c",
	"${FREETYPE_SOURCE_DIR}/src/base/ftgxval.c",
	"${FREETYPE_SOURCE_DIR}/src/base/ftinit.c",
	"${FREETYPE_SOURCE_DIR}/src/base/ftmm.c",
	"${FREETYPE_SOURCE_DIR}/src/base/ftotval.c",
	"${FREETYPE_SOURCE_DIR}/src/base/ftpatent.c",
	"${FREETYPE_SOURCE_DIR}/src/base/ftpfr.c",
	"${FREETYPE_SOURCE_DIR}/src/base/ftstroke.c",
	"${FREETYPE_SOURCE_DIR}/src/base/ftsynth.c",
	"${FREETYPE_SOURCE_DIR}/src/base/ftsystem.c",
	"${FREETYPE_SOURCE_DIR}/src/base/fttype1.c",
	"${FREETYPE_SOURCE_DIR}/src/base/ftwinfnt.c",
	"${FREETYPE_SOURCE_DIR}/src/bdf/bdf.c",
	"${FREETYPE_SOURCE_DIR}/src/bzip2/ftbzip2.c",
	"${FREETYPE_SOURCE_DIR}/src/cache/ftcache.c",
	"${FREETYPE_SOURCE_DIR}/src/cff/cff.c",
	"${FREETYPE_SOURCE_DIR}/src/cid/type1cid.c",
	"${FREETYPE_SOURCE_DIR}/src/gxvalid/gxvalid.c",
	"${FREETYPE_SOURCE_DIR}/src/gzip/ftgzip.c",
	"${FREETYPE_SOURCE_DIR}/src/lzw/ftlzw.c",
	"${FREETYPE_SOURCE_DIR}/src/otvalid/otvalid.c",
	"${FREETYPE_SOURCE_DIR}/src/pcf/pcf.c",
	"${FREETYPE_SOURCE_DIR}/src/pfr/pfr.c",
	"${FREETYPE_SOURCE_DIR}/src/psaux/psaux.c",
	"${FREETYPE_SOURCE_DIR}/src/pshinter/pshinter.c",
	"${FREETYPE_SOURCE_DIR}/src/psnames/psnames.c",
	"${FREETYPE_SOURCE_DIR}/src/raster/raster.c",
	"${FREETYPE_SOURCE_DIR}/src/sdf/sdf.c",
	"${FREETYPE_SOURCE_DIR}/src/svg/svg.c",
	"${FREETYPE_SOURCE_DIR}/src/smooth/smooth.c",
	"${FREETYPE_SOURCE_DIR}/src/truetype/truetype.c",
	"${FREETYPE_SOURCE_DIR}/src/type1/type1.c",
	"${FREETYPE_SOURCE_DIR}/src/type42/type42.c",
	"${FREETYPE_SOURCE_DIR}/src/winfonts/winfnt.c",
	"${FREETYPE_SOURCE_DIR}/src/sfnt/sfnt.c",
	)



foreach(file ${FREETYPE_MODULES_SOURCE})
    file(RELATIVE_PATH relative_path "${CMAKE_CURRENT_SOURCE_DIR}" "${file}")
    get_filename_component(dir_path "${relative_path}" DIRECTORY)
    string(REPLACE "/" "\\" vs_filter "${dir_path}")
    source_group("${vs_filter}" FILES "${file}")
endforeach()

add_library(freetype STATIC ${FREETYPE_MODULES_SOURCE})

target_include_directories(freetype PUBLIC 
    ${FREETYPE_SOURCE_DIR}/include
	)
target_link_libraries(freetype zlib brotli) 
