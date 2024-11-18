cmake_minimum_required(VERSION 3.8)

project(TestFixConstraintDemo CXX)

if (NOT DEFINED EDGE_ROOT_PATH)
	set(EDGE_ROOT_PATH ${CMAKE_CURRENT_SOURCE_DIR}/../../../../../)
endif()

include(${EDGE_ROOT_PATH}/CMake/Core.cmake)

edge_get_module_sources(TestFixConstraintDemo)
edge_add_module(TestFixConstraintDemo SHARED "Edge/Demo/Demos/Constraints")

target_link_libraries(TestFixConstraintDemo
	PRIVATE EdgeDemoFramework
)

edge_install_target(TestFixConstraintDemo Constraints "Demo/Demos")