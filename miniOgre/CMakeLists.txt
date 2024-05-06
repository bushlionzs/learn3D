cmake_minimum_required (VERSION 2.8)

set(MINIOGRE_LIB_NAME miniOgre)
set(MINIOGRE_INC)

if (WIN32)
add_definitions(-DNOMINMAX)
add_definitions(-D_CRT_SECURE_NO_WARNINGS)
add_definitions(-DFILAMENT_DRIVER_SUPPORTS_VULKAN)
add_definitions(-DVK_NO_PROTOTYPES)
endif()


macro(add_subdir)
    set(SUBDIR_SRC_LIST)
    foreach(DIR ${ARGV})
        list(APPEND MINIOGRE_INC ${CMAKE_CURRENT_SOURCE_DIR}/${DIR})

        list(APPEND MINIOGRE_INC_SUBDIR ${DIR})

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

    list(APPEND MINIOGRE_SRC_LIST ${SUBDIR_SRC_LIST})

    unset(SUBDIR_SRC_LIST)
    unset(SRC_FILES)
endmacro()


add_subdir(animation)
add_subdir(base)
add_subdir(component)
add_subdir(models)
add_subdir(multimedia)
add_subdir(parser)
add_subdir(particle)
add_subdir(particle/ParticleFX)
add_subdir(render/dx11Render)
add_subdir(render/dx12Render)
add_subdir(render/vulkanRender)
add_subdir(wow)
add_subdir(fg)
add_subdir(backend)
add_subdir(backend/vulkan)
add_subdir(backend/vulkan/spirv)
add_subdir(backend/vulkan/caching)


add_library(${MINIOGRE_LIB_NAME} STATIC ${MINIOGRE_SRC_LIST})



target_include_directories(${MINIOGRE_LIB_NAME}
    PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${MINIOGRE_INC}
	${GAMEUTIL_INC}
	${ROOT_INC}/3rd
	${ROOT_INC}/3rdSource/OIS/includes
	${ROOT_INC}/GameUtil
	${ROOT_INC}/GlslUtil
	${ROOT_INC}/3rd/bullet3/include
	${ROOT_INC}/3rd/ffmpeg/include
	${ROOT_INC}/3rd/stormlib
	${ROOT_INC}/3rdSource/utils/include
	${ROOT_INC}/3rdSource/math/include
	${ROOT_INC}/3rdSource/vkmemalloc/include
	${ROOT_INC}/3rdSource/bluevk/include
	${DYNETWORK_INCLUDE_HEADERS}
)

set(MINIOGRE_INC ${MINIOGRE_INC} CACHE INTERNAL "shared")
