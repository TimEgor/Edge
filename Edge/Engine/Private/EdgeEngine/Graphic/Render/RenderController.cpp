#include "RenderController.h"

#include "EdgeEngine/Core/UtilsMacros.h"

#include "EdgeEngine/EngineCore.h"
#include "EdgeEngine/Engine/IEngine.h"
#include "EdgeEngine/Graphic/Render/RenderPlugin.h"
#include "EdgeEngine/Plugin/IPluginController.h"

bool Edge::RenderController::init(const FileName& rendererPluginPath)
{
	IPluginController& pluginController = GetEngine().getPluginController();

	if (!rendererPluginPath)
	{
		const FileName pluginPath = pluginController.getNativePluginModulePath("Renderer plugin module");
		m_renderPluginHandle = pluginController.loadTypedPlugin<RenderPlugin>(pluginPath);
	}
	else
	{
		m_renderPluginHandle = pluginController.loadTypedPlugin<RenderPlugin>(rendererPluginPath);
	}

	EDGE_CHECK_INITIALIZATION(m_renderPluginHandle);

	const RenderPlugin& rendererPlugin = m_renderPluginHandle->getPluginCast<RenderPlugin>();
	m_render = rendererPlugin.createRenderer();

	EDGE_CHECK_RETURN_FALSE(m_render && m_render->init());

	return true;
}

void Edge::RenderController::release()
{
	EDGE_SAFE_DESTROY_WITH_RELEASING(m_render);

	m_renderPluginHandle.reset();
}

void Edge::RenderController::prepareData(const IRender::CameraTransforms& cameraTransforms, const IVisualizationDataController& visualizationData)
{
	assert(m_render);
	m_render->prepareData(cameraTransforms, visualizationData);
}

void Edge::RenderController::render(ITexture2D& texture)
{
	assert(m_render);
	m_render->render(texture);
}
