cmake_minimum_required (VERSION 2.8)

set(GAMEUTIL_LIB_NAME GameUtil)
set(GAMEUTIL_INC)

if (WIN32)
add_definitions(-DNOMINMAX)
add_definitions(-D_CRT_SECURE_NO_WARNINGS)
add_definitions(-DWIN32_LEAN_AND_MEAN)
endif()


macro(add_subdir)
    set(SUBDIR_SRC_LIST)
    foreach(DIR ${ARGV})
        list(APPEND GAMEUTIL_INC ${CMAKE_CURRENT_SOURCE_DIR}/${DIR})

        list(APPEND GAMEUTIL_INC_SUBDIR ${DIR})

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

    list(APPEND GAMEUTIL_SRC_LIST ${SUBDIR_SRC_LIST})

    unset(SUBDIR_SRC_LIST)
    unset(SRC_FILES)
endmacro()


add_subdir(.)
add_subdir(windows)
add_subdir(enkiTS)



add_library(${GAMEUTIL_LIB_NAME} STATIC ${GAMEUTIL_SRC_LIST})

target_include_directories(${GAMEUTIL_LIB_NAME}
    PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${GAMEUTIL_INC}
	${DYNETWORK_INCLUDE_HEADERS}
)

set(GAMEUTIL_INC ${GAMEUTIL_INC}  CACHE INTERNAL "shared")


