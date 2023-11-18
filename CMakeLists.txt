cmake_minimum_required(VERSION 3.18)
set(CMAKE_CXX_STANDARD 20)


set(ROOT_INC ${CMAKE_CURRENT_SOURCE_DIR})
project(learn3D)
set_property(GLOBAL PROPERTY USE_FOLDERS ON)
add_subdirectory(3rdSource/mariadbclient mariadbclient)
add_subdirectory(3rdSource/freetype-2.12.0 freetype)
add_subdirectory(3rdSource/LuaPlus luaplus)
add_subdirectory(3rdSource/stormlib stormlib)

set_property(TARGET mariadbclient PROPERTY FOLDER third_party)
set_property(TARGET dialog PROPERTY FOLDER third_party)
set_property(TARGET libmariadb PROPERTY FOLDER third_party)
set_property(TARGET mariadb_obj PROPERTY FOLDER third_party)
set_property(TARGET mysql_clear_password PROPERTY FOLDER third_party)
set_property(TARGET freetype PROPERTY FOLDER third_party)
set_property(TARGET luaplus PROPERTY FOLDER third_party)
set_property(TARGET stormlib PROPERTY FOLDER third_party)

add_subdirectory(GameUtil GameUtil)
add_subdirectory(GLSLUTIL GlslUtil)
add_subdirectory(miniOgre miniOgre)
add_subdirectory(MyGUI MyGUI)
add_subdirectory(Middle Middle)
add_subdirectory(GameClient GameClient)
add_subdirectory(GameServer GameServer)
add_subdirectory(GameShare GameShare)
add_subdirectory(MyGameEngine MyGameEngine)
add_subdirectory(Application/fulldemo fulldemo)

set_property(TARGET fulldemo PROPERTY FOLDER Application)






















