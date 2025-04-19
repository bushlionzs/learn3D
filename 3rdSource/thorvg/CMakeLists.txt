#Enforce the highest possible version that the current Ubuntu LTS provides
#by default. We want to be sure to have the ability to attach as many things
#to the target as modern cmake code affords us
cmake_minimum_required(VERSION 3.16 FATAL_ERROR)

file(GLOB  THORVG_MODULES_SOURCE 
    "${CMAKE_CURRENT_SOURCE_DIR}/src/common/*.cpp"
	"${CMAKE_CURRENT_SOURCE_DIR}/src/common/*.h"
	"${CMAKE_CURRENT_SOURCE_DIR}/src/loaders/svg/*.cpp"
	"${CMAKE_CURRENT_SOURCE_DIR}/src/loaders/svg/*.h"
	"${CMAKE_CURRENT_SOURCE_DIR}/src/loaders/raw/*.cpp"
	"${CMAKE_CURRENT_SOURCE_DIR}/src/loaders/raw/*.h"
	"${CMAKE_CURRENT_SOURCE_DIR}/src/loaders/jpg/*.cpp"
	"${CMAKE_CURRENT_SOURCE_DIR}/src/loaders/jpg/*.h"
	"${CMAKE_CURRENT_SOURCE_DIR}/src/loaders/external_webp/*.cpp"
	"${CMAKE_CURRENT_SOURCE_DIR}/src/loaders/external_webp/*.h"
	"${CMAKE_CURRENT_SOURCE_DIR}/src/loaders/external_png/*.cpp"
	"${CMAKE_CURRENT_SOURCE_DIR}/src/loaders/external_png/*.h"
	"${CMAKE_CURRENT_SOURCE_DIR}/src/renderer/*.cpp"
	"${CMAKE_CURRENT_SOURCE_DIR}/src/renderer/*.h"
	"${CMAKE_CURRENT_SOURCE_DIR}/src/renderer/sw_engine/*.cpp"
	"${CMAKE_CURRENT_SOURCE_DIR}/src/renderer/sw_engine/*.h"
	)

foreach(file ${THORVG_MODULES_SOURCE})
    file(RELATIVE_PATH relative_path "${CMAKE_CURRENT_SOURCE_DIR}" "${file}")
    get_filename_component(dir_path "${relative_path}" DIRECTORY)
    string(REPLACE "/" "\\" vs_filter "${dir_path}")
    source_group("${vs_filter}" FILES "${file}")
endforeach()

add_library(thorvg STATIC ${THORVG_MODULES_SOURCE})
target_include_directories(thorvg PRIVATE 
    ${CMAKE_CURRENT_SOURCE_DIR}/src/common
	${CMAKE_CURRENT_SOURCE_DIR}/src/renderer
	${CMAKE_CURRENT_SOURCE_DIR}/src/renderer/sw_engine
	${CMAKE_CURRENT_SOURCE_DIR}/src/loaders/svg
	${CMAKE_CURRENT_SOURCE_DIR}/src/loaders/raw
	${CMAKE_CURRENT_SOURCE_DIR}/src/loaders/jpg
	${CMAKE_CURRENT_SOURCE_DIR}/src/loaders/external_webp
	${CMAKE_CURRENT_SOURCE_DIR}/src/loaders/external_png
	)
target_include_directories(thorvg PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/inc ${CMAKE_CURRENT_SOURCE_DIR}/src/renderer ${CMAKE_CURRENT_SOURCE_DIR}/src/common)
target_link_libraries(thorvg zlib libwebp libpng) 
