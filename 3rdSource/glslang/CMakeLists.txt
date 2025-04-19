#Enforce the highest possible version that the current Ubuntu LTS provides
#by default. We want to be sure to have the ability to attach as many things
#to the target as modern cmake code affords us
cmake_minimum_required(VERSION 3.16 FATAL_ERROR)

file(GLOB  GLSLANG_MODULES_SOURCE 
    "${CMAKE_CURRENT_SOURCE_DIR}/glslang/GenericCodeGen/*.cpp"
	"${CMAKE_CURRENT_SOURCE_DIR}/glslang/GenericCodeGen/*.h"
	"${CMAKE_CURRENT_SOURCE_DIR}/glslang/MachineIndependent/*.cpp"
	"${CMAKE_CURRENT_SOURCE_DIR}/glslang/MachineIndependent/*.h"
	"${CMAKE_CURRENT_SOURCE_DIR}/glslang/MachineIndependent/preprocessor/*.cpp"
	"${CMAKE_CURRENT_SOURCE_DIR}/glslang/MachineIndependent/preprocessor/*.h"
	"${CMAKE_CURRENT_SOURCE_DIR}/glslang/OSDependent/Windows/*.cpp"
	"${CMAKE_CURRENT_SOURCE_DIR}/glslang/OSDependent/Windows/*.h"
	"${CMAKE_CURRENT_SOURCE_DIR}/glslang/ResourceLimits/*.cpp"
	"${CMAKE_CURRENT_SOURCE_DIR}/glslang/ResourceLimits/*.h"
	"${CMAKE_CURRENT_SOURCE_DIR}/SPIRV/*.cpp"
	"${CMAKE_CURRENT_SOURCE_DIR}/SPIRV/*.h"
	)

foreach(file ${GLSLANG_MODULES_SOURCE})
    file(RELATIVE_PATH relative_path "${CMAKE_CURRENT_SOURCE_DIR}" "${file}")
    get_filename_component(dir_path "${relative_path}" DIRECTORY)
    string(REPLACE "/" "\\" vs_filter "${dir_path}")
    source_group("${vs_filter}" FILES "${file}")
endforeach()

add_library(glslang STATIC ${GLSLANG_MODULES_SOURCE})
target_include_directories(glslang PRIVATE 
    ${CMAKE_CURRENT_SOURCE_DIR}

	)
target_include_directories(glslang PUBLIC 
    ${CMAKE_CURRENT_SOURCE_DIR}/glslang/include
	${CMAKE_CURRENT_SOURCE_DIR}/glslang/Public
	${CMAKE_CURRENT_SOURCE_DIR}
	)
#target_link_libraries(thorvg zlib libwebp png) 
