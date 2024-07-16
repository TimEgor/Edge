cmake_minimum_required(VERSION 3.23 FATAL_ERROR)

project(EdgeEngine CXX)

if (NOT DEFINED EDGE_ROOT_PATH)
	set(EDGE_ROOT_PATH ${CMAKE_CURRENT_SOURCE_DIR}/../../)
endif()

include(${EDGE_ROOT_PATH}/CMake/Core.cmake)

edge_get_module_sources(EdgeEngine)
edge_add_module(EdgeEngine STATIC "Edge")

edge_install_target(EdgeEngine EdgeEngine "")
edge_install_include(EdgeEngine EdgeEngine "" EDGE_PUBLIC_MODULE_SOURCES)