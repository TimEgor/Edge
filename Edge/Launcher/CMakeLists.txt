cmake_minimum_required(VERSION 3.23 FATAL_ERROR)

project(EdgeLauncher CXX)

if (NOT DEFINED EDGE_ROOT_PATH)
	set(EDGE_ROOT_PATH ${CMAKE_CURRENT_SOURCE_DIR}/../../)
endif()

include(${EDGE_ROOT_PATH}/CMake/Core.cmake)

edge_get_module_sources(EdgeLauncher)
edge_add_executable_module(EdgeLauncher "Edge")

target_link_libraries(EdgeLauncher
	PUBLIC
		EdgeEngine
)

edge_install_target(EdgeLauncher EdgeLauncher "")

edge_link_profile(EdgeLauncher)

edge_install_target(EdgeLauncher EdgeLauncher "Launcher")

edge_install_profile_post_build(EdgeLauncher)
edge_install_profile(EdgeLauncher "Launcher")