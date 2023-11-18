cmake_minimum_required (VERSION 2.8)

set(LUAPLUS_LIB_NAME luaplus)
set(LUAPLUS_INC)

if (WIN32)
add_definitions(-DNOMINMAX)
add_definitions(-D_CRT_SECURE_NO_WARNINGS)
add_definitions(-D__WINDOWS__)
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

    list(APPEND LUAPLUS_SRC_LIST ${SUBDIR_SRC_LIST})

    unset(SUBDIR_SRC_LIST)
    unset(SRC_FILES)
endmacro()


add_subdir(.)
add_subdir(src)




add_library(${LUAPLUS_LIB_NAME} STATIC ${LUAPLUS_SRC_LIST})


target_include_directories(${LUAPLUS_LIB_NAME}
    PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${LUAPLUS_INC}
)

set(LUAPLUS_INC ${LUAPLUS_INC}  CACHE INTERNAL "shared")

