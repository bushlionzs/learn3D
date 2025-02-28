cmake_minimum_required (VERSION 2.8)
set(CMAKE_CXX_STANDARD 17)
project(CryEngineDemo)


if (WIN32)
add_definitions(-DNOMINMAX)
add_definitions(-D_CRT_SECURE_NO_WARNINGS)
#add_definitions(-D__WINDOWS__)
add_definitions(-DNOT_USE_CRY_MEMORY_MANAGER)
add_definitions(-DCEGUI_STATIC)
endif()



macro(add_subdir)
    set(SUBDIR_SRC_LIST)
    foreach(DIR ${ARGV})
        list(APPEND CryEngineDemo_INC ${CMAKE_CURRENT_SOURCE_DIR}/${DIR})

        list(APPEND CryEngineDemo_INC_SUBDIR ${DIR})

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

    list(APPEND CryEngineDemo_SRC_LIST ${SUBDIR_SRC_LIST})

    unset(SUBDIR_SRC_LIST)
    unset(SRC_FILES)
endmacro()


add_subdir(.)
add_subdir(../common)
add_subdir(CryEngine/CryCommon/Cry3DEngine)
add_subdir(CryEngine/CryCommon/CryMath)
add_subdir(CryEngine/CryCommon/CrySTL)
add_subdir(CryEngine/CryCommon/CryString)
add_subdir(CryEngine/CryCommon/CryPhysics)
add_subdir(CryEngine/CryCommon/CryCore)
add_subdir(CryEngine/CryCommon/CryCore/Assert)
add_subdir(CryEngine/Cry3DEngine)
add_subdir(CryEngine/Cry3DEngine/CGF)
add_subdir(CryEngine/CrySystem)
add_subdir(CryEngine/CrySystem/XML)
add_subdir(CryEngine/CrySystem/JobManager)
add_subdir(CryEngine/CrySystem/JobManager/PCBackEnd)
add_subdir(CryEngine/CrySystem/JobManager/BlockingBackend)
add_subdir(CryEngine/CrySystem/Profiling)
add_subdir(CryEngine/CrySystem/Serialization)
add_subdir(CryEngine/CrySystem/ExtensionSystem)
add_subdir(CryEngine/CrySystem/PlatformOS)
add_subdir(CryEngine/sdks/md5)
add_subdir(CryEngine/sdks/lz4)



add_executable(${PROJECT_NAME} ${CryEngineDemo_SRC_LIST})

SET(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG  ${ROOT_INC}/bin)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${ROOT_INC}/bin)
SET(EXECUTABLE_OUTPUT_PATH ${CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG})
set_target_properties(${PROJECT_NAME} PROPERTIES VS_DEBUGGER_WORKING_DIRECTORY ${ROOT_INC}/bin)

list(APPEND CryEngineDemo_INC ${CMAKE_CURRENT_SOURCE_DIR}/CryEngine)
list(APPEND CryEngineDemo_INC ${CMAKE_CURRENT_SOURCE_DIR}/CryEngine/CryCommon)
list(APPEND CryEngineDemo_INC ${CMAKE_CURRENT_SOURCE_DIR}/CryEngine/sdks)
list(APPEND CryEngineDemo_INC ${CMAKE_CURRENT_SOURCE_DIR}/CryEngine/sdks/lz4)

target_include_directories(${PROJECT_NAME}
    PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CryEngineDemo_INC}
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
ws2_32
version
winmm
dbghelp
ntdll)
