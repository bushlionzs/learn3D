cmake_minimum_required (VERSION 2.8)

set(STORM_LIB_NAME stormlib)
set(STORMLIB_INC)

if (WIN32)
add_definitions(-DNOMINMAX)
add_definitions(-D_CRT_SECURE_NO_WARNINGS)
add_definitions(-D__WINDOWS__)
endif()


macro(add_subdir)
    set(SUBDIR_SRC_LIST)
    foreach(DIR ${ARGV})
        list(APPEND STORMLIB_INC ${CMAKE_CURRENT_SOURCE_DIR}/${DIR})

        list(APPEND STORMLIB_INC_SUBDIR ${DIR})

        file(GLOB SRC_FILES 
            ${CMAKE_CURRENT_SOURCE_DIR}/${DIR}/*.cpp 
            ${CMAKE_CURRENT_SOURCE_DIR}/${DIR}/*.c 
            ${CMAKE_CURRENT_SOURCE_DIR}/${DIR}/*.cc
            ${CMAKE_CURRENT_SOURCE_DIR}/${DIR}/*.h
            ${CMAKE_CURRENT_SOURCE_DIR}/${DIR}/*.hpp
        )
   
        list(APPEND SUBDIR_SRC_LIST ${SRC_FILES})
    endforeach()

    source_group(${ARGV0} FILES ${SUBDIR_SRC_LIST})

    list(APPEND STORMLIB_SRC_LIST ${SUBDIR_SRC_LIST})

    unset(SUBDIR_SRC_LIST)
    unset(SRC_FILES)
endmacro()


add_subdir(src)
add_subdir(src/adpcm)
add_subdir(src/bzip2)
add_subdir(src/huffman)
add_subdir(src/jenkins)
add_subdir(src/lzma/C)
add_subdir(src/pklib)
add_subdir(src/sparse)
add_subdir(src/zlib)



add_library(${STORM_LIB_NAME} STATIC ${STORMLIB_SRC_LIST})



target_include_directories(${STORM_LIB_NAME}
    PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${STORMLIB_INC}
)

set(STORMLIB_INC ${STORMLIB_INC}  CACHE INTERNAL "shared")

