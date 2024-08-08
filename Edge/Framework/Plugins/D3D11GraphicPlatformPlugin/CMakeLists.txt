cmake_minimum_required(VERSION 3.8)

project(D3D11GraphicPlatformPlugin CXX)

if (NOT DEFINED EDGE_ROOT_PATH)
	set(EDGE_ROOT_PATH ${CMAKE_CURRENT_SOURCE_DIR}/../../../)
endif()

include(${EDGE_ROOT_PATH}/CMake/Core.cmake)

edge_get_module_sources(D3D11GraphicPlatformPlugin)
edge_add_module(D3D11GraphicPlatformPlugin SHARED "Edge/Framework/Plugins")

target_link_libraries(D3D11GraphicPlatformPlugin
	PRIVATE
		EdgeFramework

		d3d11.lib
		dxgi.lib
		dxguid.lib

		d3dcompiler.lib
)

edge_install_target(D3D11GraphicPlatformPlugin D3D11GraphicPlatform "Framework/Plugins")