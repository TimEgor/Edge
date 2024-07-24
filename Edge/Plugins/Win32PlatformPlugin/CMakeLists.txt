cmake_minimum_required(VERSION 3.8)

project(Win32PlatformPlugin CXX)

if (NOT DEFINED EDGE_ROOT_PATH)
	set(EDGE_ROOT_PATH ${CMAKE_CURRENT_SOURCE_DIR}/../../../)
endif()

include(${EDGE_ROOT_PATH}/CMake/Core.cmake)

edge_get_module_sources(Win32PlatformPlugin)
edge_add_module(Win32PlatformPlugin SHARED "Edge/Engine/Plugins")

target_link_libraries(Win32PlatformPlugin
	PRIVATE
		EdgeEngine

		dxguid.lib
		dinput8.lib
)

edge_install_target(Win32PlatformPlugin Win32Platform "EnginePlugins")