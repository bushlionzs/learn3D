cmake_minimum_required (VERSION 2.8)

set(SPIRV_CROSS_LIB_NAME SpirvTools)
set(SPIRV_CROSS_INC)

if (WIN32)
add_definitions(-DNOMINMAX)
add_definitions(-D_CRT_SECURE_NO_WARNINGS)
add_definitions(-D__WINDOWS__)
add_definitions(-DLUA_OPNAMES)
endif()


macro(add_subdir)
    set(SUBDIR_SRC_LIST)
    foreach(DIR ${ARGV})
        list(APPEND LUAPLUS_INC ${CMAKE_CURRENT_SOURCE_DIR}/${DIR})

        list(APPEND LUAPLUS_INC_SUBDIR ${DIR})

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

    list(APPEND SPIRV_CROSS_SRC_LIST ${SUBDIR_SRC_LIST})

    unset(SUBDIR_SRC_LIST)
    unset(SRC_FILES)
endmacro()


add_subdir(.)
list(APPEND SPIRV_CROSS_INC ${CMAKE_CURRENT_SOURCE_DIR})

message(${SPIRV_CROSS_SRC_LIST})

add_library(${SPIRV_CROSS_LIB_NAME} STATIC ${SPIRV_CROSS_SRC_LIST})


target_include_directories(${SPIRV_CROSS_LIB_NAME}
    PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${SPIRV_CROSS_INC}
)

set(SPIRV_CROSS_INC ${SPIRV_CROSS_INC}  CACHE INTERNAL "shared")

