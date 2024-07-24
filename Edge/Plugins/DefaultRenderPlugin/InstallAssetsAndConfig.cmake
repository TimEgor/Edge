function(edge_default_render_install)
	set(OUTPUT_DIR)
	get_target_property(OUTPUT_DIR DefaultRenderPlugin LIBRARY_OUTPUT_DIRECTORY)

	set(TPL_PLUGIN_ASSETS_PATH ${CMAKE_CURRENT_LIST_DIR}/Assets)
	configure_file(${CMAKE_CURRENT_LIST_DIR}/DefaultRenderPluginConfig.xml.tpl ${OUTPUT_DIR}/DefaultRenderPluginConfig.xml)

	cmake_policy(SET CMP0087 NEW)
	set(INSTALL_OUTPUT_BASE_PATH ${CMAKE_INSTALL_PREFIX}/EnginePlugins/DefaultRender/lib/${CMAKE_GENERATOR_PLATFORM}/$<CONFIG>)
	install(CODE
		"
		set(TPL_PLUGIN_ASSETS_PATH ${INSTALL_OUTPUT_BASE_PATH}/Assets)

		configure_file(${CMAKE_CURRENT_LIST_DIR}/DefaultRenderPluginConfig.xml.tpl
		${INSTALL_OUTPUT_BASE_PATH}/DefaultRenderPluginConfig.xml)
		"
	)

	install(DIRECTORY "${CMAKE_CURRENT_LIST_DIR}/Assets" DESTINATION "EnginePlugins/DefaultRender" OPTIONAL)
endfunction()