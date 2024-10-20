cmake_minimum_required(VERSION 3.23 FATAL_ERROR)

project(EdgeCollisionDemos CXX)

if (NOT DEFINED EDGE_ROOT_PATH)
	set(EDGE_ROOT_PATH ${CMAKE_CURRENT_SOURCE_DIR}/../../../../)
endif()

include(${EDGE_ROOT_PATH}/CMake/Core.cmake)

edge_add_scope_module(EdgeCollisionDemos)

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/TestBounceCollisionDemo)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/TestGJKCollisionDemo)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/TestSpheresCollisionDemo)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/TestSpheresBoxCollisionDemo)

target_link_libraries(EdgeCollisionDemos
	INTERFACE
		TestBounceCollisionDemo
		TestGJKCollisionDemo
		TestSpheresBoxCollisionDemo
		TestSpheresCollisionDemo
)