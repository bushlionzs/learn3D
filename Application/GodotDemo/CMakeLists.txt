cmake_minimum_required (VERSION 2.8)

project(GodotDemo)
set(CMAKE_CXX_STANDARD 17)

if (WIN32)
add_definitions(-DNOMINMAX)
add_definitions(-D_CRT_SECURE_NO_WARNINGS)
add_definitions(-D__WINDOWS__)
add_definitions(-DCEGUI_STATIC)
add_definitions(-DTYPED_METHOD_BIND)
add_definitions(-DNOT_USE_STD_STRING)
add_definitions(-DWINDOWS_ENABLED)
add_definitions(-DTOOLS_ENABLED)
add_definitions(-DDEBUG_METHODS_ENABLED)
add_definitions(-DDEBUG_ENABLED)
add_definitions(-DMODULE_JSONRPC_ENABLED)
add_definitions(-DMODULE_GLSLANG_ENABLED)
add_definitions(-DMODULE_TEXT_SERVER_ADV_ENABLED)
add_definitions(-DMODULE_SVG_ENABLED)
add_definitions(-DMODULE_FREETYPE_ENABLED)
add_definitions(-DWASAPI_ENABLED)
add_definitions(-DRD_ENABLED)
add_definitions(-DVULKAN_ENABLED)
add_definitions(-DGODOT_MODULE)
add_definitions(-DTVG_STATIC)
add_definitions(-DU_STATIC_IMPLEMENTATION)
add_definitions(-DU_HAVE_LIB_SUFFIX=1)
add_definitions(-DU_LIB_SUFFIX_C_NAME=_godot)
add_definitions(-DICU_STATIC_DATA)

endif()

add_compile_options(/utf-8)
add_compile_options(/bigobj)

if(MSVC)
    # MSVC: 禁用 C4996 警告（过时函数警告）
    add_compile_options(/wd4828)
    add_compile_options(/wd4005)
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
add_subdir(godot/core/extension)
add_subdir(godot/core/crypto)
add_subdir(godot/core/debugger)

add_subdir(godot/scene)
add_subdir(godot/scene/audio)
add_subdir(godot/scene/2d)
add_subdir(godot/scene/2d/physics)
add_subdir(godot/scene/2d/physics/joints)
add_subdir(godot/scene/3d)
add_subdir(godot/scene/3d/physics)
add_subdir(godot/scene/3d/physics/joints)
add_subdir(godot/scene/main)
add_subdir(godot/scene/theme)
add_subdir(godot/scene/resources)
add_subdir(godot/scene/resources/3d)
add_subdir(godot/scene/resources/2d)
add_subdir(godot/scene/resources/2d/skeleton)
add_subdir(godot/scene/gui)
add_subdir(godot/scene/animation)
add_subdir(godot/scene/debugger)


add_subdir(godot/servers)
add_subdir(godot/servers/audio)
add_subdir(godot/servers/audio/effects)
add_subdir(godot/servers/camera)
add_subdir(godot/servers/navigation)
add_subdir(godot/servers/rendering)
add_subdir(godot/servers/rendering/renderer_rd)
add_subdir(godot/servers/rendering/renderer_rd/storage_rd)
add_subdir(godot/servers/rendering/renderer_rd/environment)
add_subdir(godot/servers/rendering/renderer_rd/effects)
add_subdir(godot/servers/rendering/renderer_rd/forward_clustered)
add_subdir(godot/servers/rendering/renderer_rd/forward_mobile)
add_subdir(godot/servers/rendering/storage)
add_subdir(godot/servers/display)
add_subdir(godot/servers/debugger)
add_subdir(godot/servers/text)
add_subdir(godot/servers/movie_writer)
add_subdir(godot/servers/extensions)

add_subdir(godot/modules)
add_subdir(godot/modules/gdscript)
add_subdir(godot/modules/gdscript/editor)
add_subdir(godot/modules/gdscript/language_server)
add_subdir(godot/modules/jsonrpc)
add_subdir(godot/modules/glslang)
add_subdir(godot/modules/text_server_adv)
add_subdir(godot/modules/freetype)
add_subdir(godot/modules/svg)

add_subdir(godot/platform)
add_subdir(godot/platform/windows)
add_subdir(godot/platform/windows/api)
add_subdir(godot/platform/windows/export)
#add_subdir(godot/platform/android)
add_subdir(godot/platform/android/api)
add_subdir(godot/platform/android/export)
#add_subdir(godot/platform/ios)
add_subdir(godot/platform/ios/api)
add_subdir(godot/platform/ios/export)
#add_subdir(godot/platform/linuxbsd)
add_subdir(godot/platform/linuxbsd/api)
add_subdir(godot/platform/linuxbsd/export)
#add_subdir(godot/platform/macos)
add_subdir(godot/platform/macos/api)
add_subdir(godot/platform/macos/export)
#add_subdir(godot/platform/web)
add_subdir(godot/platform/web/api)
add_subdir(godot/platform/web/export)


add_subdir(godot/thirdparty/zstd/common)
add_subdir(godot/thirdparty/zstd/compress)
add_subdir(godot/thirdparty/zstd/decompress)
add_subdir(godot/thirdparty/misc)
add_subdir(godot/thirdparty/mbedtls/library)
add_subdir(godot/thirdparty/vulkan)


add_subdir(godot/drivers)
add_subdir(godot/drivers/windows)
add_subdir(godot/drivers/unix)
add_subdir(godot/drivers/wasapi)
add_subdir(godot/drivers/png)
add_subdir(godot/drivers/vulkan)

add_subdir(godot/editor)
add_subdir(godot/editor/themes)
add_subdir(godot/editor/debugger)
add_subdir(godot/editor/debugger/debug_adapter)
add_subdir(godot/editor/export)
add_subdir(godot/editor/gui)
add_subdir(godot/editor/import)
add_subdir(godot/editor/import/3d)
add_subdir(godot/editor/plugins)
add_subdir(godot/editor/plugins/gizmos)
add_subdir(godot/editor/plugins/shader)
add_subdir(godot/editor/plugins/tiles)
add_subdir(godot/editor/project_manager)

add_subdir(godot/main)

add_executable(${PROJECT_NAME} ${GODOT_SRC_LIST})

SET(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG  ${ROOT_INC}/bin)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${ROOT_INC}/bin)
SET(EXECUTABLE_OUTPUT_PATH ${CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG})
set_target_properties(${PROJECT_NAME} PROPERTIES VS_DEBUGGER_WORKING_DIRECTORY ${ROOT_INC}/bin)


list(APPEND GODOT_INC ${CMAKE_CURRENT_SOURCE_DIR}/../Common)
list(APPEND GODOT_INC ${CMAKE_CURRENT_SOURCE_DIR}/Godot)
list(APPEND GODOT_INC ${CMAKE_CURRENT_SOURCE_DIR}/Godot/platform/windows)
list(APPEND GODOT_INC ${CMAKE_CURRENT_SOURCE_DIR}/Godot/thirdparty/mbedtls/include)
list(APPEND GODOT_INC ${CMAKE_CURRENT_SOURCE_DIR}/Godot/thirdparty/vulkan/include)
list(APPEND GODOT_INC ${CMAKE_CURRENT_SOURCE_DIR}/Godot/thirdparty/vulkan)
list(APPEND GODOT_INC ${CMAKE_CURRENT_SOURCE_DIR}/Godot/thirdparty/glslang/glslang/include)
list(APPEND GODOT_INC ${CMAKE_CURRENT_SOURCE_DIR}/Godot/thirdparty/glslang/glslang/Public)
list(APPEND GODOT_INC ${CMAKE_CURRENT_SOURCE_DIR}/Godot/thirdparty/thorvg/inc)
list(APPEND GODOT_INC ${CMAKE_CURRENT_SOURCE_DIR}/Godot/thirdparty/thorvg/src/renderer)
list(APPEND GODOT_INC ${CMAKE_CURRENT_SOURCE_DIR}/Godot/thirdparty/thorvg/src/common)

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
libpng
libwebp
glslang
thorvg
harfbuzz
icu4c
freetype
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
Iphlpapi
imm32
dwmapi
version
Avrt
wbemuuid
)
