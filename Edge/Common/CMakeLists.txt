cmake_minimum_required(VERSION 3.23 FATAL_ERROR)

project(EdgeCommon CXX)

if (NOT DEFINED EDGE_ROOT_PATH)
	set(EDGE_ROOT_PATH ${CMAKE_CURRENT_SOURCE_DIR}/../../)
endif()

include(${EDGE_ROOT_PATH}/CMake/Core.cmake)

edge_get_module_sources(EdgeCommon)
edge_add_module(EdgeCommon STATIC "Edge")


edge_link_profile(EdgeCommon)

# Compute math impl
set(COMPUTE_MATH DX)

target_compile_definitions(EdgeCommon
	PUBLIC EDGE_MATH_${COMPUTE_MATH}
)

edge_install_include(EdgeCommon EdgeCommon "" EDGE_PUBLIC_MODULE_SOURCES)