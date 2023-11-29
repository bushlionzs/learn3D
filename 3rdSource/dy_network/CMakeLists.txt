cmake_minimum_required (VERSION 2.8)

set(DY_NETWORK_LIB_NAME dy_network)

set(DY_NETWORK_SUBDIR)
set(DY_NETWORK_SRC_LIST)
set(DY_NETWORK_INC)

if (WIN32)
add_definitions(-DNOMINMAX)
add_definitions(-D_CRT_SECURE_NO_WARNINGS)
add_definitions(-DWIN32_LEAN_AND_MEAN)
endif()


macro(dy_network_add_subdir)
    set(SUBDIR_SRC_LIST)
    foreach(DIR ${ARGV})
        message(STATUS "dy_network subdir:" ${DIR})

        list(APPEND DY_NETWORK_INC ${CMAKE_CURRENT_SOURCE_DIR}/${DIR})

        list(APPEND DY_NETWORK_SUBDIR ${DIR})

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

    list(APPEND DY_NETWORK_SRC_LIST ${SUBDIR_SRC_LIST})

    unset(SUBDIR_SRC_LIST)
    unset(SRC_FILES)
endmacro()

if (WIN32)
    dy_network_add_subdir(net net/windows)
    dy_network_add_subdir(common common/windows)
else()
    if (APPLE)
        dy_network_add_subdir(net net/mac)
    else()
        dy_network_add_subdir(net net/linux)
    endif()

    dy_network_add_subdir(common common/linux)
endif()

dy_network_add_subdir(utility)
dy_network_add_subdir(minizip)



add_library(${DY_NETWORK_LIB_NAME} STATIC ${DY_NETWORK_SRC_LIST})

if(MSVC)
set_property(TARGET ${DY_NETWORK_LIB_NAME} PROPERTY MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")
endif()


target_include_directories(${DY_NETWORK_LIB_NAME}
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
        ${DY_NETWORK_INC}
		${BORINGSSL_INCLUDE_DIRECTORIES}
		${ZLIB_INCLUDE_DIRECTORIES}
)

target_compile_definitions(${DY_NETWORK_LIB_NAME}
    PUBLIC
        __STDC_FORMAT_MACROS
)

target_compile_features(${DY_NETWORK_LIB_NAME}
    PUBLIC
        cxx_std_11
)

if (INSTALL_INC_DIR)
    foreach(dir ${DY_NETWORK_SUBDIR})
        file(GLOB DY_NETWORK_INC ${CMAKE_CURRENT_SOURCE_DIR}/${dir}/*.h ${CMAKE_CURRENT_SOURCE_DIR}/${dir}/*.hpp)
        install(FILES ${DY_NETWORK_INC} DESTINATION ${INSTALL_INC_DIR}/${DY_NETWORK_LIB_NAME}/${dir})
    endforeach(dir)
endif()

if (INSTALL_LIB_DIR)
    install(TARGETS ${DY_NETWORK_LIB_NAME} ARCHIVE DESTINATION ${INSTALL_LIB_DIR})
endif()
