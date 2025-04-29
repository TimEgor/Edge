cmake_minimum_required(VERSION 3.23 FATAL_ERROR)

project(Edge CXX)

set(EDGE_ROOT_PATH ${CMAKE_CURRENT_SOURCE_DIR})

include(${EDGE_ROOT_PATH}/CMake/Core.cmake)

if (DEFINED EDGE_ASAN AND EDGE_ASAN)
    message("${EDGE_COLOUR_RED}\n>>>>> ASAN <<<<<\n${EDGE_COLOUR_RESET}")
    add_compile_options(-fsanitize=address)
endif()

add_subdirectory(${EDGE_ROOT_PATH}/Edge/Common)
add_subdirectory(${EDGE_ROOT_PATH}/Edge/Physics)
add_subdirectory(${EDGE_ROOT_PATH}/Edge/Framework)
add_subdirectory(${EDGE_ROOT_PATH}/Edge/Demo)

message("${EDGE_COLOUR_YELLOW}\n>>>>> Success <<<<<\n${EDGE_COLOUR_RESET}")