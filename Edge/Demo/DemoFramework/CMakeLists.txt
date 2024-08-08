cmake_minimum_required(VERSION 3.23 FATAL_ERROR)

project(EdgeDemoFramework CXX)

if (NOT DEFINED EDGE_ROOT_PATH)
	set(EDGE_ROOT_PATH ${CMAKE_CURRENT_SOURCE_DIR}/../../../)
endif()

include(${EDGE_ROOT_PATH}/CMake/Core.cmake)

edge_get_module_sources(EdgeDemoFramework)
edge_add_module(EdgeDemoFramework STATIC "Edge/Demo")

target_link_libraries(EdgeDemoFramework
	PUBLIC
		EdgeFramework
)

edge_install_target(EdgeDemoFramework EdgeDemoFramework "Demo")