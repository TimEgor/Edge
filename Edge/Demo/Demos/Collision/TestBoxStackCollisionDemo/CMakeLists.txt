cmake_minimum_required(VERSION 3.8)

project(TestBoxStackCollisionDemo CXX)

if (NOT DEFINED EDGE_ROOT_PATH)
	set(EDGE_ROOT_PATH ${CMAKE_CURRENT_SOURCE_DIR}/../../../../../)
endif()

include(${EDGE_ROOT_PATH}/CMake/Core.cmake)

edge_get_module_sources(TestBoxStackCollisionDemo)
edge_add_module(TestBoxStackCollisionDemo SHARED "Edge/Demo/Demos/Collision")

target_link_libraries(TestBoxStackCollisionDemo
	PRIVATE EdgeDemoFramework
)

edge_install_target(TestBoxStackCollisionDemo Collision "Demo/Demos")