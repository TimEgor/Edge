cmake_minimum_required(VERSION 3.23 FATAL_ERROR)

project(EdgeFrameworkScope CXX)

if (NOT DEFINED EDGE_ROOT_PATH)
	set(EDGE_ROOT_PATH ${CMAKE_CURRENT_SOURCE_DIR}/../../)
endif()

include(${EDGE_ROOT_PATH}/CMake/Core.cmake)

edge_add_scope_module(EdgeFrameworkScope)

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/Framework)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/Plugins)

target_link_libraries(EdgeFrameworkScope
	INTERFACE
		EdgeFramework
		EdgeFrameworkPlugins
)