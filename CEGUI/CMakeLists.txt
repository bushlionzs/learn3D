cmake_minimum_required (VERSION 2.8)

set(CEGUI_LIB_NAME CEGUI)
set(CEGUI_INC)

if (WIN32)
add_definitions(-DNOMINMAX)
add_definitions(-D_CRT_SECURE_NO_WARNINGS)
add_definitions(-D_SILENCE_CXX17_ITERATOR_BASE_CLASS_DEPRECATION_WARNING)
endif()


macro(add_subdir)
    set(SUBDIR_SRC_LIST)
    foreach(DIR ${ARGV})
        list(APPEND CEGUI_INC ${CMAKE_CURRENT_SOURCE_DIR}/${DIR})

        list(APPEND CEGUI_INC_SUBDIR ${DIR})

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

    list(APPEND CEGUI_SRC_LIST ${SUBDIR_SRC_LIST})

    unset(SUBDIR_SRC_LIST)
    unset(SRC_FILES)
endmacro()

add_subdir(.)
add_subdir(CEGUI/expatParser)
add_subdir(CEGUI/src)
add_subdir(CEGUI/include)
add_subdir(CEGUI/include/elements)
add_subdir(CEGUI/include/falagard)
add_subdir(CEGUI/src/elements)
add_subdir(CEGUI/src/falagard)
add_subdir(CEGUI/src/pcre)
add_subdir(CEGUIFalagardEx/include)
add_subdir(CEGUIFalagardEx/include/Extend)
add_subdir(CEGUIFalagardEx/Interface)
add_subdir(CEGUIFalagardEx/src)
add_subdir(CEGUIFalagardEx/Extend)
add_subdir(CEGUIRenderer/3DUI)
add_subdir(CEGUIRenderer/include)
add_subdir(CEGUIRenderer/src)



add_library(${CEGUI_LIB_NAME} STATIC ${CEGUI_SRC_LIST})



target_include_directories(${CEGUI_LIB_NAME}
    PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CEGUI_INC}
	${MINIOGRE_INC}
	${GAMEUTIL_INC}
	${GAMESHARE_INC}
	${ROOT_INC}/3rd
	${ROOT_INC}/3rdSource/expat/lib
	${ROOT_INC}/3rdSource/OIS/includes
	${ROOT_INC}/3rdSource/freetype-2.12.0/include
	${DYNETWORK_INCLUDE_HEADERS}
)


set(CEGUI_INC ${CEGUI_INC}  CACHE INTERNAL "shared")