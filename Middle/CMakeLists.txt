cmake_minimum_required (VERSION 2.8)

set(MIDDLE_LIB_NAME Middle)
set(MIDDLE_INC)

if (WIN32)
add_definitions(-DNOMINMAX)
add_definitions(-D_CRT_SECURE_NO_WARNINGS)
add_definitions(-D__WINDOWS__)
endif()


macro(add_subdir)
    set(SUBDIR_SRC_LIST)
    foreach(DIR ${ARGV})
        list(APPEND MIDDLE_INC ${CMAKE_CURRENT_SOURCE_DIR}/${DIR})

        list(APPEND MIDDLE_INC_SUBDIR ${DIR})

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

    list(APPEND MIDDLE_SRC_LIST ${SUBDIR_SRC_LIST})

    unset(SUBDIR_SRC_LIST)
    unset(SRC_FILES)
endmacro()


add_subdir(AdvancedAnimation)
add_subdir(component)
add_subdir(effect)
add_subdir(general)
add_subdir(Navigate)
add_subdir(Physics)
add_subdir(scene)
add_subdir(scene/scene_actor)



add_library(${MIDDLE_LIB_NAME} STATIC ${MIDDLE_SRC_LIST})



target_include_directories(${MIDDLE_LIB_NAME}
    PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
	${GAMEUTIL_INC}
    ${MIDDLE_INC}
	${MINIOGRE_INC}
	${GAMESHARE_INC}
	${ROOT_INC}/3rd
	${ROOT_INC}/3rd/Opcode
	${ROOT_INC}/3rd/bullet3/include
	${ROOT_INC}/3rdSource/utils/include
	${DYNETWORK_INCLUDE_HEADERS}
)


set(MIDDLE_INC ${MIDDLE_INC}  CACHE INTERNAL "shared")