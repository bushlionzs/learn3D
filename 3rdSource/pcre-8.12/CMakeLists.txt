cmake_minimum_required (VERSION 2.8)

set(PCRE_LIB_NAME pcre)
set(PCRE_INC)

if (WIN32)
add_definitions(-DNOMINMAX)
add_definitions(-D_CRT_SECURE_NO_WARNINGS)
add_definitions(-D__WINDOWS__)
endif()



add_library(${PCRE_LIB_NAME} STATIC pcre.c chartables.c get.c maketables.c pcreposix.c study.c)


target_include_directories(${PCRE_LIB_NAME}
    PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${PCRE_INC}
)

set(PCRE_INC ${PCRE_INC}  CACHE INTERNAL "shared")

