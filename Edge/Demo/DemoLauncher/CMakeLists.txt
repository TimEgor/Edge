cmake_minimum_required(VERSION 3.23 FATAL_ERROR)

project(EdgeDemoLauncher CXX)

if (NOT DEFINED EDGE_ROOT_PATH)
	set(EDGE_ROOT_PATH ${CMAKE_CURRENT_SOURCE_DIR}/../../../)
endif()

include(${EDGE_ROOT_PATH}/CMake/Core.cmake)

edge_get_module_sources(EdgeDemoLauncher)
edge_add_executable_module(EdgeDemoLauncher "Edge/Demo")

target_link_libraries(EdgeDemoLauncher
	PUBLIC
		EdgeDemoFramework
)

edge_link_profile(EdgeDemoLauncher)

edge_install_target(EdgeDemoLauncher EdgeDemoLauncher "Demo")

edge_install_profile_post_build(EdgeDemoLauncher)
edge_install_profile(EdgeDemoLauncher "Demo")

if (MSVC)
	set(PLATFORM_OUTPUT_DIRECTORY)
	get_target_property(PLATFORM_OUTPUT_DIRECTORY Win32PlatformPlugin LIBRARY_OUTPUT_DIRECTORY)
	set(PLATFORM_OUTPUT_NAME)
	get_target_property(PLATFORM_OUTPUT_NAME Win32PlatformPlugin OUTPUT_NAME)

	set(GRAPHIC_PLATFORM_OUTPUT_DIRECTORY)
	get_target_property(GRAPHIC_PLATFORM_OUTPUT_DIRECTORY D3D11GraphicPlatformPlugin LIBRARY_OUTPUT_DIRECTORY)
	set(GRAPHIC_PLATFORM_OUTPUT_NAME)
	get_target_property(GRAPHIC_PLATFORM_OUTPUT_NAME D3D11GraphicPlatformPlugin OUTPUT_NAME)

	set(RENDER_OUTPUT_DIRECTORY)
	get_target_property(RENDER_OUTPUT_DIRECTORY DefaultRenderPlugin LIBRARY_OUTPUT_DIRECTORY)
	set(RENDER_OUTPUT_NAME)
	get_target_property(RENDER_OUTPUT_NAME DefaultRenderPlugin OUTPUT_NAME)

	set(ARGUMENTS
		"--platform=${PLATFORM_OUTPUT_DIRECTORY}/${PLATFORM_OUTPUT_NAME}.dll \
--graphic=${GRAPHIC_PLATFORM_OUTPUT_DIRECTORY}/${GRAPHIC_PLATFORM_OUTPUT_NAME}.dll \
--renderer=${RENDER_OUTPUT_DIRECTORY}/${RENDER_OUTPUT_NAME}.dll"
	)

	set_target_properties(EdgeDemoLauncher PROPERTIES
		VS_DEBUGGER_COMMAND_ARGUMENTS ${ARGUMENTS})
endif()