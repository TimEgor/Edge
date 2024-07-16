###############################################
######             PROFILE              #######
###############################################

### edge_link_profile
function(edge_link_profile TARGET_NAME)
	set(MODULE_FOUND)
	edge_find_third_party_module(SuperluminalAPI MODULE_FOUND)
	if (${MODULE_FOUND})
		target_compile_definitions(${TARGET_NAME} PRIVATE EDGE_PROFILE_SUPERLUMINAL)
		target_link_libraries(${TARGET_NAME} PRIVATE SuperluminalAPI)
	endif()

	edge_find_third_party_module(WinPixEventRuntime MODULE_FOUND)
	if (${MODULE_FOUND})
		target_compile_definitions(${TARGET_NAME} PRIVATE EDGE_PROFILE_PIX)
		target_link_libraries(${TARGET_NAME} PRIVATE WinPixEventRuntime)
	endif()
endfunction()

### edge_install_profile_post_build
function(edge_install_profile_post_build TARGET_NAME)
	get_target_property(OUTPUT_LOCATION ${TARGET_NAME} RUNTIME_OUTPUT_DIRECTORY)

	if (TARGET WinPixEventRuntime)
		add_custom_command(TARGET ${TARGET_NAME} POST_BUILD
			COMMAND ${CMAKE_COMMAND} -E copy ${EDGE_THIRD_PARTY_PATH}/WinPixEventRuntime/bin/x64/WinPixEventRuntime.dll ${OUTPUT_LOCATION}
		)
	endif()
endfunction()

### edge_install_profile
function(edge_install_profile CURRENT_MODULE_NAME INSTALL_PATH_BASE)
	set(TARGET_LIB_INSTALL_PATH)
	edge_get_install_target_path(${CURRENT_MODULE_NAME} "${INSTALL_PATH_BASE}" TARGET_LIB_INSTALL_PATH)

	if (TARGET WinPixEventRuntime)
		install(FILES "${EDGE_THIRD_PARTY_PATH}/WinPixEventRuntime/bin/x64/WinPixEventRuntime.dll" DESTINATION ${TARGET_LIB_INSTALL_PATH} OPTIONAL)
	endif()
endfunction()