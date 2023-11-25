cmake_minimum_required (VERSION 2.8)

set(GLSLUTIL_LIB_NAME GlslUtil)
set(GLSLUTIL_INC)

if (WIN32)
add_definitions(-DNOMINMAX)
add_definitions(-D_CRT_SECURE_NO_WARNINGS)
add_definitions(-DWIN32_LEAN_AND_MEAN)
endif()


macro(add_subdir)
    set(SUBDIR_SRC_LIST)
    foreach(DIR ${ARGV})
        list(APPEND GLSLUTIL_INC ${CMAKE_CURRENT_SOURCE_DIR}/${DIR})

        list(APPEND GLSLUTIL_INC_SUBDIR ${DIR})

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

    list(APPEND GLSLUTIL_SRC_LIST ${SUBDIR_SRC_LIST})

    unset(SUBDIR_SRC_LIST)
    unset(SRC_FILES)
endmacro()


add_subdir(.)



add_library(${GLSLUTIL_LIB_NAME} SHARED ${GLSLUTIL_SRC_LIST})

SET(LIBRARY_OUTPUT_PATH  ${ROOT_INC}/bin)

target_include_directories(${GLSLUTIL_LIB_NAME}
    PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${GLSLUTIL_INC}
	${ROOT_INC}/3rd
)

set( MyFavLib_LIBRARIES 
    debug shaderc_sharedd.lib optimized shaderc_shared.lib
    debug SpirvToolsd.lib optimized SpirvTools.lib )
	
message(${MyFavLib_LIBRARIES})
target_link_directories(${GLSLUTIL_LIB_NAME}  PRIVATE ${ROOT_INC}/3rd/lib)

target_link_libraries(${GLSLUTIL_LIB_NAME} ${MyFavLib_LIBRARIES})
set(GLSLUTIL_INC ${GLSLUTIL_INC}  CACHE INTERNAL "shared")


