#pragma once

#include "EdgeFramework/Graphics/Render/RendererPlugin.h"

namespace EdgeDefRender
{
	class DefaultRendererPlugin final : public Edge::RendererPlugin
	{
	public:
		DefaultRendererPlugin(Edge::PluginModuleID moduleID)
			: RendererPlugin(moduleID) {}

		virtual void onLoaded() override;

		virtual Edge::Renderer* createRenderer() const override;
	};
}