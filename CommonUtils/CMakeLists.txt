cmake_minimum_required (VERSION 2.8)

set(COMMONUTILS_LIB_NAME CommonUtils)
set(COMMONUTILS_INC)

if (WIN32)
add_definitions(-DNOMINMAX)
add_definitions(-D_CRT_SECURE_NO_WARNINGS)
add_definitions(-DWIN32_LEAN_AND_MEAN)
endif()


macro(add_subdir)
    set(SUBDIR_SRC_LIST)
    foreach(DIR ${ARGV})
        list(APPEND COMMONUTILS_INC ${CMAKE_CURRENT_SOURCE_DIR}/${DIR})

        list(APPEND COMMONUTILS_INC_SUBDIR ${DIR})

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

    list(APPEND COMMONUTILS_SRC_LIST ${SUBDIR_SRC_LIST})

    unset(SUBDIR_SRC_LIST)
    unset(SRC_FILES)
endmacro()

add_subdir(.)
add_subdir(file)
add_subdir(string)
add_subdir(log)
add_subdir(misc)
add_subdir(net)
add_subdir(thread)
add_subdir(time)



add_library(${COMMONUTILS_LIB_NAME} STATIC ${COMMONUTILS_SRC_LIST})

target_include_directories(${COMMONUTILS_LIB_NAME}
    PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${COMMONUTILS_INC}
)

target_link_libraries(${COMMONUTILS_LIB_NAME} utils)



