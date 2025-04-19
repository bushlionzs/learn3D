#Enforce the highest possible version that the current Ubuntu LTS provides
#by default. We want to be sure to have the ability to attach as many things
#to the target as modern cmake code affords us
cmake_minimum_required(VERSION 3.16 FATAL_ERROR)

add_definitions(-D_CRT_SECURE_NO_WARNINGS)
add_definitions(-DU_STATIC_IMPLEMENTATION)
add_definitions(-DU_COMMON_IMPLEMENTATION)
add_definitions(-DUCONFIG_NO_COLLATION)
add_definitions(-DUCONFIG_NO_CONVERSION)
add_definitions(-DUCONFIG_NO_FORMATTING)
add_definitions(-DUCONFIG_NO_SERVICE)
add_definitions(-DUCONFIG_NO_IDNA)
add_definitions(-DUCONFIG_NO_FILE_IO)
add_definitions(-DUCONFIG_NO_TRANSLITERATION)
add_definitions(-DUCONFIG_NO_REGULAR_EXPRESSIONS)
add_definitions(-DPKGDATA_MODE=static)
add_definitions(-DU_ENABLE_DYLOAD=0)
add_definitions(-DU_HAVE_LIB_SUFFIX=1)
add_definitions(-DU_LIB_SUFFIX_C_NAME=_godot)
add_definitions(-DU_COMMON_IMPLEMENTATION)

add_compile_options(/utf-8)

file(GLOB  ICU4C_MODULES_SOURCE 
    "${CMAKE_CURRENT_SOURCE_DIR}/common/*.cpp"
	"${CMAKE_CURRENT_SOURCE_DIR}/common/*.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/common/unicode/*.cpp"
	"${CMAKE_CURRENT_SOURCE_DIR}/common/unicode/*.h"
	"${CMAKE_CURRENT_SOURCE_DIR}/i18n/*.cpp"
	"${CMAKE_CURRENT_SOURCE_DIR}/i18n/*.h"
	)

foreach(file ${ICU4C_MODULES_SOURCE})
    file(RELATIVE_PATH relative_path "${CMAKE_CURRENT_SOURCE_DIR}" "${file}")
    get_filename_component(dir_path "${relative_path}" DIRECTORY)
    string(REPLACE "/" "\\" vs_filter "${dir_path}")
    source_group("${vs_filter}" FILES "${file}")
endforeach()

add_library(icu4c STATIC ${ICU4C_MODULES_SOURCE})
target_include_directories(icu4c PRIVATE 
    ${CMAKE_CURRENT_SOURCE_DIR}/common

	)
target_include_directories(icu4c PUBLIC 
	${CMAKE_CURRENT_SOURCE_DIR}
	${CMAKE_CURRENT_SOURCE_DIR}/common
	${CMAKE_CURRENT_SOURCE_DIR}/i18n
	)
#target_link_libraries(thorvg zlib libwebp png) 
