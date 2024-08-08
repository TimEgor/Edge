cmake_minimum_required(VERSION 3.23 FATAL_ERROR)

project(EdgePhysics CXX)

if (NOT DEFINED EDGE_ROOT_PATH)
	set(EDGE_ROOT_PATH ${CMAKE_CURRENT_SOURCE_DIR}/../../)
endif()

include(${EDGE_ROOT_PATH}/CMake/Core.cmake)

edge_get_module_sources(EdgePhysics)
edge_add_module(EdgePhysics STATIC "Edge")

target_link_libraries(EdgePhysics
	PUBLIC
		EdgeCommon
)

edge_install_target(EdgePhysics EdgePhysics "")
edge_install_include(EdgePhysics EdgePhysics "" EDGE_PUBLIC_MODULE_SOURCES)