set(EDGE_THIRD_PARTY_PATH ${EDGE_ROOT_PATH}/ThirdParty)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${EDGE_THIRD_PARTY_PATH}/FindModules)

###############################################
######              BUILD               #######
###############################################

### edge_build_module
function(edge_build_module MODULE_NAME IS_REQUIRED)
	set(MODULE_PATH ${EDGE_THIRD_PARTY_PATH}/${MODULE_NAME})

	if (NOT EXISEDGE ${MODULE_PATH})
		if (${IS_REQUIRED})
			message(FATAL_ERROR "Error: Third party module '${MODULE_NAME}' hasn't been found.")
		else()
			return()
		endif()
	endif()

	set(MODULE_NEED_INSTALL FALSE)

	set(THIRD_PARTY_MODULE_BUILD_ARGS_PATH ${EDGE_THIRD_PARTY_PATH}/BuildArgs/${MODULE_NAME}.cmake)
	if (EXISEDGE ${THIRD_PARTY_MODULE_BUILD_ARGS_PATH})
		include(${THIRD_PARTY_MODULE_BUILD_ARGS_PATH})
	endif()

	set(MODULE_BINARY_PATH ${MODULE_PATH}/Build)
	if (EXISEDGE ${MODULE_BINARY_PATH})
		file(REMOVE_RECURSE ${MODULE_BINARY_PATH})
	endif()

	file(MAKE_DIRECTORY ${MODULE_BINARY_PATH})

	execute_process(COMMAND ${CMAKE_COMMAND} -A ${CMAKE_GENERATOR_PLATFORM} ${MODULE_PATH} ${MODULE_CONFIG_ARGS}
		-DCMAKE_INSTALL_PREFIX=${EDGE_THIRD_PARTY_PATH}/Install/${CMAKE_GENERATOR_PLATFORM}/${MODULE_INSTALL_DIR}
		WORKING_DIRECTORY ${MODULE_BINARY_PATH}
	)

	if (NOT DEFINED PREBUILD_CONFIGURATIONS)
		set(PREBUILD_CONFIGURATIONS "Debug" "Release")
	endif()

	foreach(CONFIGURATION ${PREBUILD_CONFIGURATIONS})
		execute_process(COMMAND ${CMAKE_COMMAND} --build . --config ${CONFIGURATION}
			WORKING_DIRECTORY ${MODULE_BINARY_PATH}
		)
	endforeach()

	if (${MODULE_NEED_INSTALL})
		foreach(CONFIGURATION ${PREBUILD_CONFIGURATIONS})
			execute_process(COMMAND ${CMAKE_COMMAND} --install . --config ${CONFIGURATION}
				WORKING_DIRECTORY ${MODULE_BINARY_PATH}
			)
		endforeach()
	endif()
endfunction()

###############################################
######               FIND               #######
###############################################

#edge_find_third_party_module
function(edge_find_third_party_module MODULE_NAME RESULT)
	set(MODULE_FOUND TRUE)

	if ((NOT ${${MODULE_NAME}_FOUND}) OR (NOT DEFINED ${MODULE_NAME}_FOUND))
		find_package(${MODULE_NAME})

		if ((NOT ${${MODULE_NAME}_FOUND}) OR (NOT DEFINED ${MODULE_NAME}_FOUND))
			set(MODULE_FOUND FALSE)
		endif()
	endif()

	set(${RESULT} ${MODULE_FOUND} PARENT_SCOPE)
endfunction()

#edge_find_or_build_third_party_module
function(edge_find_or_build_third_party_module MODULE_NAME RESULT)
	set(MODULE_FOUND TRUE)

	edge_find_third_party_module(${MODULE_NAME} MODULE_FOUND)
	if (NOT ${MODULE_FOUND})
		edge_build_module(${MODULE_NAME} TRUE)
		edge_find_third_party_module(${MODULE_NAME} MODULE_FOUND)
	endif()

	set(${RESULT} ${MODULE_FOUND} PARENT_SCOPE)
endfunction()

#edge_import_third_party_module
function(edge_import_third_party_module MODULE_NAME)
	set(MODULE_FOUND TRUE)
	edge_find_or_build_third_party_module(${MODULE_NAME} MODULE_FOUND)
	if (NOT ${MODULE_FOUND})
		message(FATAL_ERROR "Error: Third party module '${MODULE_NAME}' hasn't been found.")
	endif()
endfunction()