cmake_minimum_required(VERSION 3.8)

project(FireworksDemo CXX)

if (NOT DEFINED TS_ROOT_PATH)
	set(TS_ROOT_PATH ${CMAKE_CURRENT_SOURCE_DIR}/../../../../)
endif()

include(${TS_ROOT_PATH}/CMake/Core.cmake)

ts_get_module_sources(FireworksDemo)
ts_add_module(FireworksDemo SHARED "TinySim/Demo/Demos")

target_link_libraries(FireworksDemo
	PRIVATE TinySimDemoFramework
)

ts_install_target(FireworksDemo Fireworks "Demo/Demos")