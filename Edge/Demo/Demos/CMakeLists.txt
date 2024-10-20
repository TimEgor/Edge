cmake_minimum_required(VERSION 3.23 FATAL_ERROR)

project(EdgeDemos CXX)

if (NOT DEFINED EDGE_ROOT_PATH)
	set(EDGE_ROOT_PATH ${CMAKE_CURRENT_SOURCE_DIR}/../../../)
endif()

include(${EDGE_ROOT_PATH}/CMake/Core.cmake)

edge_add_scope_module(EdgeDemos)

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/DebugDrawDemo)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/FireworksDemo)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/TestCastDemo)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/Collision)

target_link_libraries(EdgeDemos
	INTERFACE
		DebugDrawDemo
		FireworksDemo
		TestCastDemo
		EdgeCollisionDemos
)