cmake_minimum_required(VERSION 3.23 FATAL_ERROR)

project(EdgeConstraintsDemos CXX)

if (NOT DEFINED EDGE_ROOT_PATH)
	set(EDGE_ROOT_PATH ${CMAKE_CURRENT_SOURCE_DIR}/../../../../)
endif()

include(${EDGE_ROOT_PATH}/CMake/Core.cmake)

edge_add_scope_module(EdgeConstraintsDemos)

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/TestFixConstraintDemo)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/TestKeepDistanceConstraintDemo)

target_link_libraries(EdgeConstraintsDemos
	INTERFACE
		TestFixConstraintDemo
		TestKeepDistanceConstraintDemo
)