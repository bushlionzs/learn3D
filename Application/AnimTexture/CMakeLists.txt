cmake_minimum_required (VERSION 2.8)

project(AnimTexture)


if (WIN32)
add_definitions(-DNOMINMAX)
add_definitions(-D_CRT_SECURE_NO_WARNINGS)
add_definitions(-D__WINDOWS__)
endif()


macro(add_subdir)
    set(SUBDIR_SRC_LIST)
    foreach(DIR ${ARGV})
        list(APPEND GAMECLIENT_INC ${CMAKE_CURRENT_SOURCE_DIR}/${DIR})

        list(APPEND GAMECLIENT_INC_SUBDIR ${DIR})

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

    list(APPEND GAMECLIENT_SRC_LIST ${SUBDIR_SRC_LIST})

    unset(SUBDIR_SRC_LIST)
    unset(SRC_FILES)
endmacro()


add_subdir(.)
add_subdir(../common)





add_executable(${PROJECT_NAME} ${GAMECLIENT_SRC_LIST})

SET(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG  ${ROOT_INC}/bin)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${ROOT_INC}/bin)
SET(EXECUTABLE_OUTPUT_PATH ${CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG})
set_target_properties(${PROJECT_NAME} PROPERTIES VS_DEBUGGER_WORKING_DIRECTORY ${ROOT_INC}/bin)
target_include_directories(${PROJECT_NAME}
    PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${GAMECLIENT_INC}
	${GAMEUTIL_INC}
	${GAMESHARE_INC}
	${MIDDLE_INC}
	${MINIOGRE_INC}
	${MYGUI_INC}
	${ROOT_INC}/3rd/OIS/include
)

target_link_directories(${PROJECT_NAME}  PRIVATE ${ROOT_INC}/3rd/lib)


	
target_link_libraries(${PROJECT_NAME} GameUtil GlslUtil miniOgre 
MyGUI Middle stormlib OIS LinearMath BulletCollision BulletDynamics BulletSoftBody
tinyxmld
vulkan-1
avcodec
avdevice
avfilter
avformat
avutil
postproc
swresample
swscale
dxgi
dxguid
d3d12
d3d11
D3DCompiler
Shlwapi
winmm)
