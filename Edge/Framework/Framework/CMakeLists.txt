cmake_minimum_required(VERSION 3.23 FATAL_ERROR)

project(EdgeFramework CXX)

if (NOT DEFINED EDGE_ROOT_PATH)
	set(EDGE_ROOT_PATH ${CMAKE_CURRENT_SOURCE_DIR}/../../)
endif()

include(${EDGE_ROOT_PATH}/CMake/Core.cmake)

edge_get_module_sources(EdgeFramework)
edge_add_module(EdgeFramework STATIC "Edge/Framework")

edge_import_third_party_module(PugiXML)

target_link_libraries(EdgeFramework
	PUBLIC
		EdgePhysics

		pugixml::pugixml
)

edge_install_target(EdgeFramework EdgeFramework "")
edge_install_include(EdgeFramework EdgeFramework "" EDGE_PUBLIC_MODULE_SOURCES)