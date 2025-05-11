#Enforce the highest possible version that the current Ubuntu LTS provides
#by default. We want to be sure to have the ability to attach as many things
#to the target as modern cmake code affords us
cmake_minimum_required(VERSION 3.16 FATAL_ERROR)

set(SPIRV-REFLECT_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR})

file(GLOB  SPIRV-REFLECT_MODULES_SOURCE "${SPIRV-REFLECT_SOURCE_DIR}/*.c" "${SPIRV-REFLECT_SOURCE_DIR}/*.h")

foreach(file ${SPIRV-REFLECT_MODULES_SOURCE})
    file(RELATIVE_PATH relative_path "${CMAKE_CURRENT_SOURCE_DIR}" "${file}")
    get_filename_component(dir_path "${relative_path}" DIRECTORY)
    string(REPLACE "/" "\\" vs_filter "${dir_path}")
    source_group("${vs_filter}" FILES "${file}")
endforeach()

add_library(spirv-reflect STATIC ${SPIRV-REFLECT_MODULES_SOURCE})
target_include_directories(spirv-reflect PUBLIC 
${SPIRV-REFLECT_SOURCE_DIR}
${SPIRV-REFLECT_SOURCE_DIR}/include)
target_link_libraries(spirv-reflect zlib ) 
