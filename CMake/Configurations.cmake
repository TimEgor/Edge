if(NOT DEFINED EDGE_CONFIGURATIONS)
	set(EDGE_CONFIGURATIONS)

	set(EDGE_CONFIGURATION_TYPES Debug Release Profile Retail)

	set(CMAKE_C_FLAGS_RETAIL ${CMAKE_C_FLAGS_RELEASE})
	set(CMAKE_CXX_FLAGS_RETAIL ${CMAKE_CXX_FLAGS_RELEASE})
	set(CMAKE_EXE_LINKER_FLAGS_RETAIL ${CMAKE_EXE_LINKER_FLAGS_RELEASE})
	set(CMAKE_SHARED_LINKER_FLAGS_RETAIL ${CMAKE_SHARED_LINKER_FLAGS_RELEASE})
	
	set(CMAKE_C_FLAGS_PROFILE ${CMAKE_C_FLAGS_RELWITHDEBINFO})
	set(CMAKE_CXX_FLAGS_PROFILE ${CMAKE_CXX_FLAGS_RELWITHDEBINFO})
	set(CMAKE_EXE_LINKER_FLAGS_PROFILE ${CMAKE_EXE_LINKER_FLAGS_RELWITHDEBINFO})
	set(CMAKE_SHARED_LINKER_FLAGS_PROFILE ${CMAKE_SHARED_LINKER_FLAGS_RELWITHDEBINFO})
	
	set(CMAKE_C_FLAGS_RELEASE ${CMAKE_C_FLAGS_RELWITHDEBINFO})
	set(CMAKE_CXX_FLAGS_RELEASE ${CMAKE_CXX_FLAGS_RELWITHDEBINFO})
	set(CMAKE_EXE_LINKER_FLAGS_RELEASE ${CMAKE_EXE_LINKER_FLAGS_RELWITHDEBINFO})
	set(CMAKE_SHARED_LINKER_FLAGS_RELEASE ${CMAKE_SHARED_LINKER_FLAGS_RELWITHDEBINFO})
	
	add_compile_definitions(
		EDGE_CONFIG=$<CONFIG>
		EDGE_CONFIG_NAME="$<CONFIG>"
	
		$<$<CONFIG:Debug>:EDGE_CONFIG_DEBUG>
		$<$<CONFIG:Release>:EDGE_CONFIG_RELEASE>
		$<$<CONFIG:Profile>:EDGE_CONFIG_PROFILE>
		$<$<CONFIG:Retail>:EDGE_CONFIG_RETAIL>
	)
	
	set(CMAKE_CONFIGURATION_TYPES ${EDGE_CONFIGURATION_TYPES})
endif()