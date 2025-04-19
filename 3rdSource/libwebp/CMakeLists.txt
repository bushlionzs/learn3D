#Enforce the highest possible version that the current Ubuntu LTS provides
#by default. We want to be sure to have the ability to attach as many things
#to the target as modern cmake code affords us
cmake_minimum_required(VERSION 3.16 FATAL_ERROR)


file(GLOB  LIBWEBP_MODULES_SOURCE
    "${CMAKE_CURRENT_SOURCE_DIR}/src/utils/*.c"
	"${CMAKE_CURRENT_SOURCE_DIR}/src/utils/*.h"
	"${CMAKE_CURRENT_SOURCE_DIR}/src/mux/*.c"
	"${CMAKE_CURRENT_SOURCE_DIR}/src/mux/*.h"
	"${CMAKE_CURRENT_SOURCE_DIR}/src/enc/*.c"
	"${CMAKE_CURRENT_SOURCE_DIR}/src/enc/*.h"
	"${CMAKE_CURRENT_SOURCE_DIR}/src/dsp/*.c"
	"${CMAKE_CURRENT_SOURCE_DIR}/src/dsp/*.h"
	"${CMAKE_CURRENT_SOURCE_DIR}/src/demux/*.c"
	"${CMAKE_CURRENT_SOURCE_DIR}/src/demux/*.h"
	"${CMAKE_CURRENT_SOURCE_DIR}/src/dec/*.c"
	"${CMAKE_CURRENT_SOURCE_DIR}/src/dec/*.h"
	"${CMAKE_CURRENT_SOURCE_DIR}/sharpyuv/*.c"
	"${CMAKE_CURRENT_SOURCE_DIR}/sharpyuv/*.h"
	)

foreach(file ${LIBWEBP_MODULES_SOURCE})
    file(RELATIVE_PATH relative_path "${CMAKE_CURRENT_SOURCE_DIR}" "${file}")
    get_filename_component(dir_path "${relative_path}" DIRECTORY)
    string(REPLACE "/" "\\" vs_filter "${dir_path}")
    source_group("${vs_filter}" FILES "${file}")
endforeach()

add_library(libwebp STATIC ${LIBWEBP_MODULES_SOURCE})
target_include_directories(libwebp PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
target_include_directories(libwebp PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src)

