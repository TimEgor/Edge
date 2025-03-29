cmake_minimum_required(VERSION 3.8)

project(TestPrismaticConstraintDemo CXX)

if (NOT DEFINED EDGE_ROOT_PATH)
	set(EDGE_ROOT_PATH ${CMAKE_CURRENT_SOURCE_DIR}/../../../../../)
endif()

include(${EDGE_ROOT_PATH}/CMake/Core.cmake)

edge_get_module_sources(TestPrismaticConstraintDemo)
edge_add_module(TestPrismaticConstraintDemo SHARED "Edge/Demo/Demos/Constraints")

target_link_libraries(TestPrismaticConstraintDemo
	PRIVATE EdgeDemoFramework
)

edge_install_target(TestPrismaticConstraintDemo Constraints "Demo/Demos")