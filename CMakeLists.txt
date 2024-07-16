cmake_minimum_required(VERSION 3.23 FATAL_ERROR)

project(Edge CXX)

set(EDGE_ROOT_PATH ${CMAKE_CURRENT_SOURCE_DIR})

include(${EDGE_ROOT_PATH}/CMake/Core.cmake)

#add_compile_options(-fsanitize=address)

add_subdirectory(${EDGE_ROOT_PATH}/Edge/Engine)
#add_subdirectory(${EDGE_ROOT_PATH}/Edge/EnginePlugins)
add_subdirectory(${EDGE_ROOT_PATH}/Edge/Launcher)

message("${EDGE_COLOUR_YELLOW}\n>>>>> Success <<<<<\n${EDGE_COLOUR_RESET}")