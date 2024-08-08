cmake_minimum_required(VERSION 3.23 FATAL_ERROR)

project(EdgeFrameworkPlugins CXX)

if (NOT DEFINED EDGE_ROOT_PATH)
	set(EDGE_ROOT_PATH ${CMAKE_CURRENT_SOURCE_DIR}/../../../)
endif()

include(${EDGE_ROOT_PATH}/CMake/Core.cmake)

edge_add_scope_module(EdgeFrameworkPlugins)

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/Win32PlatformPlugin)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/D3D11GraphicPlatformPlugin)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/DefaultRenderPlugin)

target_link_libraries(EdgeFrameworkPlugins
	INTERFACE
		Win32PlatformPlugin
		D3D11GraphicPlatformPlugin
		DefaultRenderPlugin
)