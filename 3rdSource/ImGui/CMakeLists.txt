#Enforce the highest possible version that the current Ubuntu LTS provides
#by default. We want to be sure to have the ability to attach as many things
#to the target as modern cmake code affords us
cmake_minimum_required(VERSION 3.16 FATAL_ERROR)


file(GLOB  IMGUI_MODULES_SOURCE 
    "${CMAKE_CURRENT_SOURCE_DIR}/source/*.cpp"
	"${CMAKE_CURRENT_SOURCE_DIR}/source/*.h"
	"${CMAKE_CURRENT_SOURCE_DIR}/source/ImGuizmo/*.cpp"
	"${CMAKE_CURRENT_SOURCE_DIR}/source/ImGuizmo/*.h"
	)

foreach(file ${IMGUI_MODULES_SOURCE})
    file(RELATIVE_PATH relative_path "${CMAKE_CURRENT_SOURCE_DIR}" "${file}")
    get_filename_component(dir_path "${relative_path}" DIRECTORY)
    string(REPLACE "/" "\\" vs_filter "${dir_path}")
    source_group("${vs_filter}" FILES "${file}")
endforeach()

add_library(imgui STATIC ${IMGUI_MODULES_SOURCE})

target_include_directories(imgui PUBLIC 
    ${CMAKE_CURRENT_SOURCE_DIR}
	${CMAKE_CURRENT_SOURCE_DIR}/source
	)
target_link_libraries(imgui
freetype)
