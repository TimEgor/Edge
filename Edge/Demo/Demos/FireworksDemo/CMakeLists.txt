cmake_minimum_required(VERSION 3.8)

project(FireworksDemo CXX)

if (NOT DEFINED EDGE_ROOT_PATH)
	set(EDGE_ROOT_PATH ${CMAKE_CURRENT_SOURCE_DIR}/../../../../)
endif()

include(${EDGE_ROOT_PATH}/CMake/Core.cmake)

edge_get_module_sources(FireworksDemo)
edge_add_module(FireworksDemo SHARED "Edge/Demo/Demos")

target_link_libraries(FireworksDemo
	PRIVATE EdgeDemoFramework
)

edge_install_target(FireworksDemo Fireworks "Demo/Demos")