cmake_minimum_required(VERSION 3.18)
set(CMAKE_CXX_STANDARD 20)
set(ROOT_INC ${CMAKE_CURRENT_SOURCE_DIR})
project(learn3D_cmake)
set_property(GLOBAL PROPERTY USE_FOLDERS ON)
add_subdirectory(3rdSource/zlib zlib)
add_subdirectory(3rdSource/boringssl boringssl)
add_subdirectory(3rdSource/protobuf protobuf)
add_subdirectory(3rdSource/dy_network dy_network)
add_subdirectory(3rdSource/mariadbclient mariadbclient)
add_subdirectory(3rdSource/freetype-2.12.0 freetype)
add_subdirectory(3rdSource/OIS OIS)
add_subdirectory(3rdSource/LuaPlus luaplus)
add_subdirectory(3rdSource/stormlib stormlib)
add_subdirectory(3rdSource/bullet3 bullet3)
add_subdirectory(3rdSource/expat expat)
add_subdirectory(3rdSource/pcre-8.12 pcre)
add_subdirectory(3rdSource/libiconv-1.14 iconv)

set_property(TARGET zlibstatic PROPERTY FOLDER third_party)
set_property(TARGET crypto PROPERTY FOLDER third_party)
set_property(TARGET ssl PROPERTY FOLDER third_party)
set_property(TARGET fipsmodule PROPERTY FOLDER third_party)
set_property(TARGET libprotobuf PROPERTY FOLDER third_party)
set_property(TARGET libprotobuf-lite PROPERTY FOLDER third_party)
set_property(TARGET dy_network PROPERTY FOLDER third_party)
set_property(TARGET mariadbclient PROPERTY FOLDER third_party)
set_property(TARGET dialog PROPERTY FOLDER third_party)
set_property(TARGET libmariadb PROPERTY FOLDER third_party)
set_property(TARGET mariadb_obj PROPERTY FOLDER third_party)
set_property(TARGET mysql_clear_password PROPERTY FOLDER third_party)
set_property(TARGET freetype PROPERTY FOLDER third_party)
set_property(TARGET OIS PROPERTY FOLDER third_party)
set_property(TARGET luaplus PROPERTY FOLDER third_party)
set_property(TARGET stormlib PROPERTY FOLDER third_party)
set_property(TARGET expat PROPERTY FOLDER third_party)
set_property(TARGET elements PROPERTY FOLDER third_party)
set_property(TARGET element_declarations PROPERTY FOLDER third_party)
set_property(TARGET benchmark PROPERTY FOLDER third_party)
set_property(TARGET outline PROPERTY FOLDER third_party)
set_property(TARGET runtests PROPERTY FOLDER third_party)
set_property(TARGET runtests_cxx PROPERTY FOLDER third_party)
set_property(TARGET xmlwf PROPERTY FOLDER third_party)
set_property(TARGET iconv PROPERTY FOLDER third_party)
set_property(TARGET pcre PROPERTY FOLDER third_party)
set_property(TARGET pcreposix PROPERTY FOLDER third_party)



set_property(TARGET Bullet2FileLoader PROPERTY FOLDER third_party/bullet3)
set_property(TARGET Bullet3Collision PROPERTY FOLDER third_party/bullet3)
set_property(TARGET Bullet3Common PROPERTY FOLDER third_party/bullet3)
set_property(TARGET Bullet3Dynamics PROPERTY FOLDER third_party/bullet3)
set_property(TARGET Bullet3Geometry PROPERTY FOLDER third_party/bullet3)
set_property(TARGET Bullet3OpenCL_clew PROPERTY FOLDER third_party/bullet3)
set_property(TARGET BulletCollision PROPERTY FOLDER third_party/bullet3)
set_property(TARGET BulletDynamics PROPERTY FOLDER third_party/bullet3)
set_property(TARGET BulletInverseDynamics PROPERTY FOLDER third_party/bullet3)
set_property(TARGET BulletSoftBody PROPERTY FOLDER third_party/bullet3)
set_property(TARGET LinearMath PROPERTY FOLDER third_party/bullet3)


add_subdirectory(GameUtil GameUtil)
add_subdirectory(GLSLUTIL GlslUtil)
add_subdirectory(miniOgre miniOgre)
add_subdirectory(MyGUI MyGUI)
add_subdirectory(cegui0.8.7 CEGUI)
add_subdirectory(GameShare GameShare)
add_subdirectory(Middle Middle)
add_subdirectory(GameServer GameServer)
add_subdirectory(GameClient GameClient)
add_subdirectory(Application/AnimTexture AnimTexture)
add_subdirectory(Application/basic basic)
add_subdirectory(Application/fulldemo fulldemo)
add_subdirectory(Application/GameUI GameUI)
add_subdirectory(Application/gltfModel gltfModel)
add_subdirectory(Application/particle particle)
add_subdirectory(Application/RenderToTexture RenderToTexture)
add_subdirectory(Application/ShadowMap ShadowMap)
add_subdirectory(Application/SkeletonAnimation SkeletonAnimation)
add_subdirectory(Application/UITest UITest)
add_subdirectory(Application/VideoTexture VideoTexture)
add_subdirectory(Application/wowMap wowMap)
set_property(TARGET AnimTexture PROPERTY FOLDER Application)
set_property(TARGET basic PROPERTY FOLDER Application)
set_property(TARGET fulldemo PROPERTY FOLDER Application)
set_property(TARGET GameUI PROPERTY FOLDER Application)
set_property(TARGET gltfModel PROPERTY FOLDER Application)
set_property(TARGET particle PROPERTY FOLDER Application)
set_property(TARGET RenderToTexture PROPERTY FOLDER Application)
set_property(TARGET ShadowMap PROPERTY FOLDER Application)
set_property(TARGET SkeletonAnimation PROPERTY FOLDER Application)
set_property(TARGET UITest PROPERTY FOLDER Application)
set_property(TARGET VideoTexture PROPERTY FOLDER Application)
set_property(TARGET wowMap PROPERTY FOLDER Application)






















