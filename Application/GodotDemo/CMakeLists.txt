cmake_minimum_required (VERSION 2.8)

project(GodotDemo)


if (WIN32)
add_definitions(-DNOMINMAX)
add_definitions(-D_CRT_SECURE_NO_WARNINGS)
add_definitions(-D__WINDOWS__)
add_definitions(-DCEGUI_STATIC)
add_definitions(-DTYPED_METHOD_BIND)
add_definitions(-DNOT_USE_STD_STRING)
add_definitions(-DWINDOWS_ENABLED)
endif()


macro(add_subdir)
    set(SUBDIR_SRC_LIST)
    foreach(DIR ${ARGV})

        list(APPEND GODOT_INC_SUBDIR ${DIR})

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

    list(APPEND GODOT_SRC_LIST ${SUBDIR_SRC_LIST})

    unset(SUBDIR_SRC_LIST)
    unset(SRC_FILES)
endmacro()


add_subdir(.)
add_subdir(../common)
add_subdir(godot/core)
add_subdir(godot/core/config)
add_subdir(godot/core/io)
add_subdir(godot/core/variant)
add_subdir(godot/core/error)
add_subdir(godot/core/object)
add_subdir(godot/core/templates)
add_subdir(godot/core/string)
add_subdir(godot/core/os)
add_subdir(godot/core/object)
add_subdir(godot/core/math)
add_subdir(godot/core/input)
#add_subdir(godot/core/extension)
add_subdir(godot/core/crypto)

add_subdir(godot/scene)
add_subdir(godot/scene/3d)
add_subdir(godot/scene/3d/physics)
add_subdir(godot/scene/main)
add_subdir(godot/scene/theme)
add_subdir(godot/scene/resources)
add_subdir(godot/scene/resources/3d)
add_subdir(godot/scene/main)
add_subdir(godot/servers)

add_subdir(godot/platform/windows)
add_subdir(godot/thirdparty/zstd/common)
add_subdir(godot/thirdparty/zstd/compress)
add_subdir(godot/thirdparty/zstd/decompress)
add_subdir(godot/thirdparty/misc)
add_subdir(godot/thirdparty/mbedtls/library)

add_subdir(godot/drivers/windows)
add_subdir(godot/drivers/unix)

add_executable(${PROJECT_NAME} ${GODOT_SRC_LIST})

SET(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG  ${ROOT_INC}/bin)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${ROOT_INC}/bin)
SET(EXECUTABLE_OUTPUT_PATH ${CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG})
set_target_properties(${PROJECT_NAME} PROPERTIES VS_DEBUGGER_WORKING_DIRECTORY ${ROOT_INC}/bin)


list(APPEND GODOT_INC ${CMAKE_CURRENT_SOURCE_DIR}/../Common)
list(APPEND GODOT_INC ${CMAKE_CURRENT_SOURCE_DIR}/Godot)
list(APPEND GODOT_INC ${CMAKE_CURRENT_SOURCE_DIR}/Godot/platform/windows)
list(APPEND GODOT_INC ${CMAKE_CURRENT_SOURCE_DIR}/Godot/thirdparty/mbedtls/include)

target_include_directories(${PROJECT_NAME}
    PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${GODOT_INC}
	${GAMEUTIL_INC}
	${GAMESHARE_INC}
	${MIDDLE_INC}
	${MINIOGRE_INC}
	${ROOT_INC}/3rd/OIS/include
)

target_link_directories(${PROJECT_NAME}  PRIVATE ${ROOT_INC}/3rd/lib)

	
target_link_libraries(${PROJECT_NAME}  GameUtil  miniOgre 
CEGUI expat  stormlib OIS freetype dy_network 
tinyxmld
pcre
dxgi
dxguid
d3d12
d3d11
D3DCompiler
Shlwapi
winmm
dbghelp
bcrypt
dwrite
Crypt32
ntdll
Iphlpapi)
