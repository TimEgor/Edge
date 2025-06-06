set(MODULE_NEED_INSTALL TRUE)
set(MODULE_INSTALL_DIR "PugiXML")
set(PREBUILD_CONFIGURATIONS "Release" "Debug" "RelWithDebInfo")

set(MODULE_CONFIG_ARGS
	-DPUGIXML_USE_POSTFIX=ON
)

if (DEFINED EDGE_ASAN AND EDGE_ASAN)
	set(MODULE_CONFIG_ARGS
		${MODULE_CONFIG_ARGS}
		-DCMAKE_CXX_FLAGS="${CMAKE_CXX_FLAGS} -fsanitize=address"
	)
endif()