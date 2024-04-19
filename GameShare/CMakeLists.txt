cmake_minimum_required (VERSION 2.8)

set(GAMESHARE_LIB_NAME GameShare)
set(GAMESHARE_INC)

if (WIN32)
add_definitions(-DNOMINMAX)
add_definitions(-D_CRT_SECURE_NO_WARNINGS)
add_definitions(-D__WINDOWS__)
endif()


macro(add_subdir)
    set(SUBDIR_SRC_LIST)
    foreach(DIR ${ARGV})
        list(APPEND GAMESHARE_INC ${CMAKE_CURRENT_SOURCE_DIR}/${DIR})

        list(APPEND GAMESHARE_INC_SUBDIR ${DIR})

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

    list(APPEND GAMESHARE_SRC_LIST ${SUBDIR_SRC_LIST})

    unset(SUBDIR_SRC_LIST)
    unset(SRC_FILES)
endmacro()


add_subdir(.)
add_subdir(dummy)
add_subdir(net)
add_subdir(net/messages)


add_library(${GAMESHARE_LIB_NAME} STATIC ${GAMESHARE_SRC_LIST})



target_include_directories(${GAMESHARE_LIB_NAME}
    PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${GAMESHARE_INC}
	${MINIOGRE_INC}
	${GAMEUTIL_INC}
	${ROOT_INC}/3rdSource/utils/include
	${GAMESERVER_INC}
	${LUAPLUS_INC}
	${PROTOBUF_INC}
	${DYNETWORK_INCLUDE_HEADERS}
	
)

set(GAMESHARE_INC ${GAMESHARE_INC}  CACHE INTERNAL "shared")

