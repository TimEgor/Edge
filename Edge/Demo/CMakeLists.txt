cmake_minimum_required(VERSION 3.23 FATAL_ERROR)

project(EdgeDemoScope CXX)

if (NOT DEFINED EDGE_ROOT_PATH)
	set(EDGE_ROOT_PATH ${CMAKE_CURRENT_SOURCE_DIR}/../../)
endif()

include(${EDGE_ROOT_PATH}/CMake/Core.cmake)

edge_add_scope_module(EdgeDemoScope)

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/DemoFramework)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/DemoLauncher)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/Demos)

target_link_libraries(EdgeDemoScope
	INTERFACE
		EdgeDemoFramework
		EdgeDemoLauncher
		EdgeDemos
)