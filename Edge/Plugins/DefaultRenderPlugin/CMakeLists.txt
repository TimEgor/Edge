cmake_minimum_required(VERSION 3.8)

project(DefaultRenderPlugin CXX)

if (NOT DEFINED EDGE_ROOT_PATH)
	set(EDGE_ROOT_PATH ${CMAKE_CURRENT_SOURCE_DIR}/../../../)
endif()

include(${EDGE_ROOT_PATH}/CMake/Core.cmake)

edge_get_module_sources(DefaultRenderPlugin)
edge_add_module(DefaultRenderPlugin SHARED "Edge/Engine/Plugins")

target_link_libraries(DefaultRenderPlugin
	PRIVATE
		EdgeEngine
)

edge_install_target(DefaultRenderPlugin DefaultRender "EnginePlugins")

include(${CMAKE_CURRENT_LIST_DIR}/InstallAssetsAndConfig.cmake)
edge_default_render_install()