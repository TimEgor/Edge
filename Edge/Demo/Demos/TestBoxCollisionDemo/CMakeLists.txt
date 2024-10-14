cmake_minimum_required(VERSION 3.8)

project(TestBoxCollisionDemo CXX)

if (NOT DEFINED EDGE_ROOT_PATH)
	set(EDGE_ROOT_PATH ${CMAKE_CURRENT_SOURCE_DIR}/../../../../)
endif()

include(${EDGE_ROOT_PATH}/CMake/Core.cmake)

edge_get_module_sources(TestBoxCollisionDemo)
edge_add_module(TestBoxCollisionDemo SHARED "Edge/Demo/Demos")

target_link_libraries(TestBoxCollisionDemo
	PRIVATE EdgeDemoFramework
)

edge_install_target(TestBoxCollisionDemo TestCollision "Demo/Demos")