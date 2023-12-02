cmake_minimum_required (VERSION 2.8)


project(GameServer)

set(GAMESERVER_LIB_NAME GameServer)
set(GAMESERVER_INC)

if (WIN32)
add_definitions(-DNOMINMAX)
add_definitions(-D_CRT_SECURE_NO_WARNINGS)
add_definitions(-D__WINDOWS__)
endif()


macro(add_subdir)
    set(SUBDIR_SRC_LIST)
    foreach(DIR ${ARGV})
        list(APPEND GAMESERVER_INC ${CMAKE_CURRENT_SOURCE_DIR}/${DIR})

        list(APPEND GAMESERVER_INC_SUBDIR ${DIR})

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

    list(APPEND GAMESERVER_SRC_LIST ${SUBDIR_SRC_LIST})

    unset(SUBDIR_SRC_LIST)
    unset(SRC_FILES)
endmacro()


add_subdir(.)
add_subdir(Archive)
add_subdir(data)
add_subdir(db)
add_subdir(dummy)
add_subdir(gameobject)
add_subdir(horse)
add_subdir(item)
add_subdir(map)
add_subdir(quest)
add_subdir(script)
add_subdir(share)
add_subdir(share/tab)
add_subdir(shop)
add_subdir(skill)



add_executable(${GAMESERVER_LIB_NAME} ${GAMESERVER_SRC_LIST})



target_include_directories(${GAMESERVER_LIB_NAME}
    PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${GAMESERVER_INC}
	${GAMEUTIL_INC}
	${GAMESHARE_INC}
    ${LUAPLUS_INC}
	${MYSQL_INC}
	${PROTOBUF_INC}
	${DYNETWORK_INCLUDE_HEADERS}
)

target_link_directories(${PROJECT_NAME}  PRIVATE ${ROOT_INC}/3rd/lib)

target_link_libraries(${PROJECT_NAME} GameUtil   
GameShare  mariadbclient luaplus dy_network LinearMath BulletCollision BulletDynamics BulletSoftBody
tinyxmld
dxgi
dxguid
winmm)


