cmake_minimum_required (VERSION 2.8)

set(compressonator_lib_name compressonator)
set(compressonator_inc)

if (WIN32)
add_definitions(-DNOMINMAX)
add_definitions(-D_CRT_SECURE_NO_WARNINGS)
add_definitions(-DWIN32_LEAN_AND_MEAN)
endif()


macro(add_subdir)
    set(SUBDIR_SRC_LIST)
    foreach(DIR ${ARGV})
        list(APPEND compressonator_inc ${CMAKE_CURRENT_SOURCE_DIR}/${DIR})

        list(APPEND compressonator_inc_subdir ${DIR})

        file(GLOB SRC_FILES 
            ${CMAKE_CURRENT_SOURCE_DIR}/${DIR}/*.cpp
			${CMAKE_CURRENT_SOURCE_DIR}/${DIR}/*.cxx
            ${CMAKE_CURRENT_SOURCE_DIR}/${DIR}/*.c 
            ${CMAKE_CURRENT_SOURCE_DIR}/${DIR}/*.cc
            ${CMAKE_CURRENT_SOURCE_DIR}/${DIR}/*.h
            ${CMAKE_CURRENT_SOURCE_DIR}/${DIR}/*.hpp
        )
   
        list(APPEND SUBDIR_SRC_LIST ${SRC_FILES})
    endforeach()

    source_group(${ARGV0} FILES ${SUBDIR_SRC_LIST})

    list(APPEND SOURCE_LIST ${SUBDIR_SRC_LIST})

    unset(SUBDIR_SRC_LIST)
    unset(SRC_FILES)
endmacro()


add_subdir(cmp_compressonatorlib)
add_subdir(cmp_compressonatorlib/apc)
add_subdir(cmp_compressonatorlib/ati)
add_subdir(cmp_compressonatorlib/atc)
add_subdir(cmp_compressonatorlib/basis)
add_subdir(cmp_compressonatorlib/bc6h)
add_subdir(cmp_compressonatorlib/bc7)
add_subdir(cmp_compressonatorlib/block)
add_subdir(cmp_compressonatorlib/buffer)
add_subdir(cmp_compressonatorlib/dxt)
add_subdir(cmp_compressonatorlib/dxtc)
add_subdir(cmp_compressonatorlib/etc)
add_subdir(cmp_compressonatorlib/etc/etcpack)
add_subdir(cmp_compressonatorlib/gt)
add_subdir(cmp_compressonatorlib/common)
add_subdir(cmp_core/shaders)
add_subdir(cmp_core/source)
add_subdir(application/_plugin/common)
add_subdir(application/_plugin/ccmp_sdk)
add_subdir(application/_plugin/ccmp_sdk/bc1)
add_subdir(application/_plugin/ccmp_sdk/bc2)
add_subdir(application/_plugin/ccmp_sdk/bc3)
add_subdir(application/_plugin/ccmp_sdk/bc4)
add_subdir(application/_plugin/ccmp_sdk/bc5)
add_subdir(application/_plugin/ccmp_sdk/bc6)
add_subdir(application/_plugin/ccmp_sdk/bc7)
#add_subdir(application/_plugin/ccmp_sdk/brlg)
add_subdir(application/_libs/cmp_math)
add_subdir(cmp_framework)
add_subdir(cmp_framework/common)
add_subdir(cmp_framework/common/half)




add_library(${compressonator_lib_name} STATIC ${SOURCE_LIST})

target_include_directories(${compressonator_lib_name}
    PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${compressonator_inc}
)

set(compressonator_inc ${compressonator_inc}  CACHE INTERNAL "shared")


