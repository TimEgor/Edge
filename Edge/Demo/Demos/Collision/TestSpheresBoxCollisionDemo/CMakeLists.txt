cmake_minimum_required(VERSION 3.8)

project(TestSpheresBoxCollisionDemo CXX)

if (NOT DEFINED EDGE_ROOT_PATH)
	set(EDGE_ROOT_PATH ${CMAKE_CURRENT_SOURCE_DIR}/../../../../../)
endif()

include(${EDGE_ROOT_PATH}/CMake/Core.cmake)

edge_get_module_sources(TestSpheresBoxCollisionDemo)
edge_add_module(TestSpheresBoxCollisionDemo SHARED "Edge/Demo/Demos/Collision")

target_link_libraries(TestSpheresBoxCollisionDemo
	PRIVATE EdgeDemoFramework
)

edge_install_target(TestSpheresBoxCollisionDemo Collision "Demo/Demos")