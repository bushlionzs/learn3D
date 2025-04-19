#Enforce the highest possible version that the current Ubuntu LTS provides
#by default. We want to be sure to have the ability to attach as many things
#to the target as modern cmake code affords us
cmake_minimum_required(VERSION 3.16 FATAL_ERROR)


file(GLOB  LIBPNG_MODULES_SOURCE 
    "${CMAKE_CURRENT_SOURCE_DIR}/*.c"
	"${CMAKE_CURRENT_SOURCE_DIR}/*.h"
	"${CMAKE_CURRENT_SOURCE_DIR}/intel/*.c"
	"${CMAKE_CURRENT_SOURCE_DIR}/intel/*.h"
	)

foreach(file ${LIBPNG_MODULES_SOURCE})
    file(RELATIVE_PATH relative_path "${CMAKE_CURRENT_SOURCE_DIR}" "${file}")
    get_filename_component(dir_path "${relative_path}" DIRECTORY)
    string(REPLACE "/" "\\" vs_filter "${dir_path}")
    source_group("${vs_filter}" FILES "${file}")
endforeach()

add_library(libpng STATIC ${LIBPNG_MODULES_SOURCE})

target_include_directories(libpng PUBLIC 
    ${CMAKE_CURRENT_SOURCE_DIR}
	)
target_link_libraries(libpng zlib) 
