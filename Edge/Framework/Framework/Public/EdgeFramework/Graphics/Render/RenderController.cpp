#include "RenderController.h"

#include "EdgeCommon/UtilsMacros.h"

#include "EdgeFramework/FrameworkCore.h"
#include "EdgeFramework/Application/Application.h"
#include "EdgeFramework/PluginController/PluginController.h"

#include "Renderer.h"
#include "RendererPlugin.h"

bool Edge::RenderController::init(const FileName& rendererPluginPath)
{
	PluginController& pluginController = FrameworkCore::getInstance().getApplication().getPluginController();

	if (!rendererPluginPath)
	{
		const FileName pluginPath = pluginController.getNativePluginModulePath("Renderer plugin module");
		m_rendererPluginHandle = pluginController.loadPlugin<RendererPlugin>(pluginPath);
	}
	else
	{
		m_rendererPluginHandle = pluginController.loadPlugin<RendererPlugin>(rendererPluginPath);
	}

	EDGE_CHECK_INITIALIZATION(m_rendererPluginHandle);

	const RendererPlugin& rendererPlugin = m_rendererPluginHandle->getPluginCast<RendererPlugin>();
	m_renderer = rendererPlugin.createRenderer();

	EDGE_CHECK_RETURN_FALSE(m_renderer && m_renderer->init());

	return true;
}

void Edge::RenderController::release()
{
	EDGE_SAFE_DESTROY_WITH_RELEASING(m_renderer);

	m_rendererPluginHandle.reset();
}

void Edge::RenderController::prepareData(const Renderer::CameraParams& cameraTransforms, const Transform& cameraTransform, const DebugVisualizationDataController& visualizationData)
{
	assert(m_renderer);
	m_renderer->prepareData(cameraTransforms, cameraTransform, visualizationData);
}

void Edge::RenderController::render(Texture2D& texture)
{
	assert(m_renderer);
	m_renderer->render(texture);
}
