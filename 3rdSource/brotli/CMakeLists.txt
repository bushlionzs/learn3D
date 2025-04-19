#Enforce the highest possible version that the current Ubuntu LTS provides
#by default. We want to be sure to have the ability to attach as many things
#to the target as modern cmake code affords us
cmake_minimum_required(VERSION 3.16 FATAL_ERROR)

set(BROTLI_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR})

file(GLOB  BROTLI_MODULES_SOURCE 
    "${BROTLI_SOURCE_DIR}/common/*.c"
	"${BROTLI_SOURCE_DIR}/common/*.h"
	"${BROTLI_SOURCE_DIR}/dec/*.c"
	"${BROTLI_SOURCE_DIR}/dec/*.h"
	)

foreach(file ${BROTLI_MODULES_SOURCE})
    file(RELATIVE_PATH relative_path "${CMAKE_CURRENT_SOURCE_DIR}" "${file}")
    get_filename_component(dir_path "${relative_path}" DIRECTORY)
    string(REPLACE "/" "\\" vs_filter "${dir_path}")
    source_group("${vs_filter}" FILES "${file}")
endforeach()

add_library(brotli STATIC ${BROTLI_MODULES_SOURCE})

target_include_directories(brotli PUBLIC 
    ${BROTLI_SOURCE_DIR}/include
	)
#target_link_libraries(etcpak zlib) 
