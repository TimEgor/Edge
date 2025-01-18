cmake_minimum_required(VERSION 3.8)

project(TestHingeConstraintDemo CXX)

if (NOT DEFINED EDGE_ROOT_PATH)
	set(EDGE_ROOT_PATH ${CMAKE_CURRENT_SOURCE_DIR}/../../../../../)
endif()

include(${EDGE_ROOT_PATH}/CMake/Core.cmake)

edge_get_module_sources(TestHingeConstraintDemo)
edge_add_module(TestHingeConstraintDemo SHARED "Edge/Demo/Demos/Constraints")

target_link_libraries(TestHingeConstraintDemo
	PRIVATE EdgeDemoFramework
)

edge_install_target(TestHingeConstraintDemo Constraints "Demo/Demos")