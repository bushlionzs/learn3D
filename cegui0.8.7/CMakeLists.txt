cmake_minimum_required (VERSION 2.8)

set(CEGUI_LIB_NAME CEGUI)
set(CEGUI_INC)

if (WIN32)
add_definitions(-DNOMINMAX)
add_definitions(-D_CRT_SECURE_NO_WARNINGS)
add_definitions(-D_SILENCE_CXX17_ITERATOR_BASE_CLASS_DEPRECATION_WARNING)
add_definitions(-DCEGUI_STATIC)
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

macro(add_subdir2)
    set(SUBDIR_SRC_LIST)
    foreach(DIR ${ARGV})
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
add_subdir(include)
add_subdir(include/CEGUI/CommonDialogs/ColourPicker)
add_subdir(include/CEGUI/falagard)
add_subdir(include/CEGUI/RendererModules/Ogre)
add_subdir(include/CEGUI/widgets)
add_subdir(include/CEGUI/WindowRendererSets/Core)
add_subdir(include/CEGUI/XMLParserModules/Expat)

add_subdir2(src)
add_subdir2(src/CommonDialogs/ColourPicker)
add_subdir2(src/falagard)
add_subdir2(src/RendererModules/Ogre)
add_subdir2(src/widgets)
add_subdir2(src/WindowRendererSets/Core)
add_subdir2(src/XMLParserModules/Expat)




add_library(${CEGUI_LIB_NAME} STATIC ${CEGUI_SRC_LIST})



target_include_directories(${CEGUI_LIB_NAME}
    PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CEGUI_INC}
	${MINIOGRE_INC}
	${GAMEUTIL_INC}
	${GAMESHARE_INC}
	${ROOT_INC}/3rd
	${ROOT_INC}/3rdSource/pcre-8.12
	${ROOT_INC}/3rdSource/expat/lib
	${ROOT_INC}/3rdSource/libiconv-1.14
	${ROOT_INC}/3rdSource/OIS/includes
	${ROOT_INC}/3rdSource/freetype-2.12.0/include
	${DYNETWORK_INCLUDE_HEADERS}
)


set(CEGUI_INC ${CEGUI_INC}  CACHE INTERNAL "shared")