cmake_minimum_required (VERSION 2.8)

set(ICONV_LIB_NAME iconv)
set(ICONV_INC)

if (WIN32)
add_definitions(-DNOMINMAX)
add_definitions(-D_CRT_SECURE_NO_WARNINGS)
add_definitions(-D__WINDOWS__)
endif()




add_library(${ICONV_LIB_NAME} STATIC iconv.c localcharset.c)


target_include_directories(${ICONV_LIB_NAME}
    PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${ICONV_INC}
)

set(ICONV_INC ${ICONV_INC}  CACHE INTERNAL "shared")

