cmake_minimum_required (VERSION 2.8)

set(MYGUI_LIB_NAME MyGUI)
set(MYGUI_INC)

if (WIN32)
add_definitions(-DNOMINMAX)
add_definitions(-D_CRT_SECURE_NO_WARNINGS)
add_definitions(-DWIN32_LEAN_AND_MEAN)
endif()


macro(add_subdir)
    set(SUBDIR_SRC_LIST)
    foreach(DIR ${ARGV})
        list(APPEND MYGUI_INC ${CMAKE_CURRENT_SOURCE_DIR}/${DIR})

        list(APPEND MYGUI_INC_SUBDIR ${DIR})

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

    list(APPEND MYGUI_SRC_LIST ${SUBDIR_SRC_LIST})

    unset(SUBDIR_SRC_LIST)
    unset(SRC_FILES)
endmacro()


add_subdir(uicommon)
add_subdir(uiengine)
add_subdir(uirender)



add_library(${MYGUI_LIB_NAME} STATIC ${MYGUI_SRC_LIST})



target_include_directories(${MYGUI_LIB_NAME}
    PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${MYGUI_INC}
	${MINIOGRE_INC}
	${GAMEUTIL_INC}
	${ROOT_INC}/3rd
	${ROOT_INC}/3rdSource/OIS/includes
	${ROOT_INC}/3rdSource/freetype-2.12.0/include
	${DYNETWORK_INCLUDE_HEADERS}
)


set(MYGUI_INC ${MYGUI_INC}  CACHE INTERNAL "shared")