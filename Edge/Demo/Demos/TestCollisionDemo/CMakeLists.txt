cmake_minimum_required(VERSION 3.8)

project(TestCollisionDemo CXX)

if (NOT DEFINED EDGE_ROOT_PATH)
	set(EDGE_ROOT_PATH ${CMAKE_CURRENT_SOURCE_DIR}/../../../../)
endif()

include(${EDGE_ROOT_PATH}/CMake/Core.cmake)

edge_get_module_sources(TestCollisionDemo)
edge_add_module(TestCollisionDemo SHARED "Edge/Demo/Demos")

target_link_libraries(TestCollisionDemo
	PRIVATE EdgeDemoFramework
)

edge_install_target(TestCollisionDemo TestCollision "Demo/Demos")