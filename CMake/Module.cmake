###############################################
######        TARGET & PROPERTIES       #######
###############################################

### edge_module_message
macro(edge_module_message MODULE_NAME COLOR)
	message("${COLOR}${EDGE_MODULE_MESSAGE_OFFSET}${MODULE_NAME}${EDGE_COLOUR_RESET}")
endmacro()

### edge_module_message_space
macro(edge_module_message_space SPACE_NAME)
	message("${EDGE_MODULE_MESSAGE_OFFSET}${SPACE_NAME}:")
	set(EDGE_MODULE_MESSAGE_OFFSET "${EDGE_MODULE_MESSAGE_OFFSET}\t")
endmacro()

### edge_set_module_default_target_properties_out_path
function(edge_set_module_default_target_properties_out_path TARGET_NAME FILTER_NAME OUTPUT_PATH)
	set_target_properties(${TARGET_NAME} PROPERTIES
		ARCHIVE_OUTPUT_DIRECTORY ${OUTPUT_PATH}
		LIBRARY_OUTPUT_DIRECTORY ${OUTPUT_PATH}
		RUNTIME_OUTPUT_DIRECTORY ${OUTPUT_PATH}
		OUTPUT_NAME "${PROJECT_NAME}_$<CONFIG>_${CMAKE_GENERATOR_PLATFORM}"
		CXX_STANDARD 17
	)

	foreach(CONFIG ${CMAKE_CONFIGURATION_TYPES})
		string(TOUPPER ${CONFIG} CONFIG)
		set_target_properties(${TARGET_NAME} PROPERTIES
			ARCHIVE_OUTPUT_DIRECTORY_${CONFIG} ${OUTPUT_PATH}
			LIBRARY_OUTPUT_DIRECTORY_${CONFIG} ${OUTPUT_PATH}
			RUNTIME_OUTPUT_DIRECTORY_${CONFIG} ${OUTPUT_PATH}
		)
	endforeach()

	set_property(GLOBAL PROPERTY USE_FOLDERS ON)
	set_target_properties(${TARGET_NAME} PROPERTIES
		FOLDER ${FILTER_NAME}
	)

	get_target_property(TARGET_TYPE ${TARGET_NAME} TYPE)
	set(PUBLIC_INCLUDE_TYPE)
	if (${TARGET_TYPE} STREQUAL "INTERFACE_LIBRARY")
		set(PUBLIC_INCLUDE_TYPE INTERFACE)
	else()
		set(PUBLIC_INCLUDE_TYPE PUBLIC)
	endif()

	target_include_directories(${TARGET_NAME}
		${PUBLIC_INCLUDE_TYPE}
			${CMAKE_CURRENT_LIST_DIR}/Public
		PRIVATE
			${CMAKE_CURRENT_LIST_DIR}/Private
	)
endfunction()

### edge_get_module_sources
macro(edge_get_module_sources MODULE_NAME)
	set(EDGE_PUBLIC_MODULE_SOURCES)
	edge_get_module_public_sources(${MODULE_NAME} EDGE_PUBLIC_MODULE_SOURCES)
	set(EDGE_PRIVATE_MODULE_SOURCES)
	edge_get_module_private_sources(${MODULE_NAME} EDGE_PRIVATE_MODULE_SOURCES)
endmacro()

### edge_get_sources
function(edge_get_sources SOURCES_PATH SOURCES)
	set(SRCS)
	edge_get_all_sources_recurse("${SOURCES_PATH}" SRCS)
	edge_generate_source_groups_by_sources("${SOURCES_PATH}" SRCS)

	list(APPEND SRCS ${${SOURCES}})
	set(${SOURCES} ${SRCS} PARENT_SCOPE)
endfunction()

### edge_get_module_public_sources
function(edge_get_module_public_sources MODULE_NAME SOURCES)
	set(PUBLIC_SOURCES)
	edge_get_sources("${CMAKE_CURRENT_LIST_DIR}/Public/${MODULE_NAME}" PUBLIC_SOURCES)

	list(APPEND PUBLIC_SOURCES ${${SOURCES}})
	set(${SOURCES} ${PUBLIC_SOURCES} PARENT_SCOPE)
endfunction()

### edge_get_module_private_sources
function(edge_get_module_private_sources MODULE_NAME SOURCES)
	set(PRIVATE_SOURCES)
	edge_get_sources("${CMAKE_CURRENT_LIST_DIR}/Private/${MODULE_NAME}" PRIVATE_SOURCES)

	list(APPEND PRIVATE_SOURCES ${${SOURCES}})
	set(${SOURCES} ${PRIVATE_SOURCES} PARENT_SCOPE)
endfunction()

### edge_add_module_target_name
function(edge_add_module_target_name TARGET_NAME MODULE_NAME LINK_MODIFIER FILTER_PATH OUTPUT_PATH PUBLIC_SRCS PRIVATE_SRCS)
	add_library(${TARGET_NAME} ${LINK_MODIFIER})
	target_sources(${TARGET_NAME}
		PRIVATE
			${${PUBLIC_SRCS}}
			${${PRIVATE_SRCS}}
	)

	edge_set_module_default_target_properties_out_path(${TARGET_NAME} ${FILTER_PATH} ${OUTPUT_PATH})
endfunction()

### edge_add_executable_target_name
function(edge_add_executable_target_name TARGET_NAME MODULE_NAME FILTER_PATH OUTPUT_PATH PUBLIC_SRCS PRIVATE_SRCS)
	add_executable(${TARGET_NAME} ${EDGE_EXE_MODIFIER})
	target_sources(${TARGET_NAME}
		PRIVATE
			${${PUBLIC_SRCS}}
			${${PRIVATE_SRCS}}
	)

	edge_set_module_default_target_properties_out_path(${TARGET_NAME} ${FILTER_PATH} ${OUTPUT_PATH})

	if (MSVC)
		set_target_properties(${TARGET_NAME} PROPERTIES
			VS_DEBUGGER_WORKING_DIRECTORY ${OUTPUT_PATH}
		)
	endif()
endfunction()

### edge_add_module
macro(edge_add_module TARGET_NAME LINK_MODIFIER FILTER_PATH)
	edge_add_module_target_name(${TARGET_NAME} ${TARGET_NAME} ${LINK_MODIFIER} ${FILTER_PATH} ${CMAKE_CURRENT_BINARY_DIR}/Out EDGE_PUBLIC_MODULE_SOURCES EDGE_PRIVATE_MODULE_SOURCES)

	set(MESSAGE_COLOR)
	if (${LINK_MODIFIER} STREQUAL INTERFACE)
		set(MESSAGE_COLOR ${EDGE_COLOR_WHITE})
	elseif (${LINK_MODIFIER} STREQUAL SHARED)
		set(MESSAGE_COLOR ${EDGE_COLOUR_MAGENTA})
	elseif (${LINK_MODIFIER} STREQUAL STATIC)
		set(MESSAGE_COLOR ${EDGE_COLOUR_GREEN})
	else ()
		set(MESSAGE_COLOR ${EDGE_COLOUR_RED})
	endif()

	edge_module_message(${TARGET_NAME} ${MESSAGE_COLOR})
endmacro()

### edge_add_executable_module
macro(edge_add_executable_module TARGET_NAME FILTER_PATH)
	edge_add_executable_target_name(${TARGET_NAME} ${TARGET_NAME} ${FILTER_PATH} ${CMAKE_CURRENT_BINARY_DIR}/Out EDGE_PUBLIC_MODULE_SOURCES EDGE_PRIVATE_MODULE_SOURCES)
	edge_module_message(${TARGET_NAME} ${EDGE_COLOUR_YELLOW})
endmacro()

### edge_add_scope_module
macro(edge_add_scope_module TARGET_NAME)
	add_library(${TARGET_NAME} INTERFACE)
	edge_module_message_space(${TARGET_NAME})
endmacro()