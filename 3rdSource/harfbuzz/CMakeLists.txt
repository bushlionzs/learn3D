#Enforce the highest possible version that the current Ubuntu LTS provides
#by default. We want to be sure to have the ability to attach as many things
#to the target as modern cmake code affords us
cmake_minimum_required(VERSION 3.16 FATAL_ERROR)
add_definitions(-DHAVE_FREETYPE)
add_definitions(-DHAVE_ICU)
add_definitions(-DU_STATIC_IMPLEMENTATION)
add_definitions(-DU_HAVE_LIB_SUFFIX=1)
add_definitions(-DU_LIB_SUFFIX_C_NAME=_godot)
add_definitions(-DHAVE_ICU_BUILTIN)


file(GLOB  HARFBUZZ_MODULES_SOURCE 
    "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cc"
	"${CMAKE_CURRENT_SOURCE_DIR}/src/*.h"
	"${CMAKE_CURRENT_SOURCE_DIR}/src/graph/*.cc"
	"${CMAKE_CURRENT_SOURCE_DIR}/src/graph/*.h"
	"${CMAKE_CURRENT_SOURCE_DIR}/src/OT/*.cc"
	"${CMAKE_CURRENT_SOURCE_DIR}/src/OT/*.h"
	"${CMAKE_CURRENT_SOURCE_DIR}/src/OT/Color/*.cc"
	"${CMAKE_CURRENT_SOURCE_DIR}/src/OT/Color/*.h"
	"${CMAKE_CURRENT_SOURCE_DIR}/src/OT/glyf/*.cc"
	"${CMAKE_CURRENT_SOURCE_DIR}/src/OT/glyf/*.h"
	"${CMAKE_CURRENT_SOURCE_DIR}/src/OT/Layout/*.cc"
	"${CMAKE_CURRENT_SOURCE_DIR}/src/OT/Layout/*.h"
	"${CMAKE_CURRENT_SOURCE_DIR}/src/OT/name/*.cc"
	"${CMAKE_CURRENT_SOURCE_DIR}/src/OT/name/*.h"
	"${CMAKE_CURRENT_SOURCE_DIR}/src/OT/Var/*.cc"
	"${CMAKE_CURRENT_SOURCE_DIR}/src/OT/Var/*.h"
	)

foreach(file ${HARFBUZZ_MODULES_SOURCE})
    file(RELATIVE_PATH relative_path "${CMAKE_CURRENT_SOURCE_DIR}" "${file}")
    get_filename_component(dir_path "${relative_path}" DIRECTORY)
    string(REPLACE "/" "\\" vs_filter "${dir_path}")
    source_group("${vs_filter}" FILES "${file}")
endforeach()

add_library(harfbuzz STATIC ${HARFBUZZ_MODULES_SOURCE})
target_include_directories(harfbuzz PRIVATE 
    ${CMAKE_CURRENT_SOURCE_DIR}

	)
target_include_directories(harfbuzz PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src)
target_link_libraries(harfbuzz freetype icu4c) 
