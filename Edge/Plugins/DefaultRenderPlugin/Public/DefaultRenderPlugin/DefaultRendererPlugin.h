#pragma once

#include "TinySimFramework/Graphics/Render/RendererPlugin.h"

namespace TS_DEF_RENDERER
{
	class DefaultRendererPlugin final : public TS::RendererPlugin
	{
	public:
		DefaultRendererPlugin(TS::PluginModuleID moduleID)
			: RendererPlugin(moduleID) {}

		virtual void onLoaded() override;

		virtual TS::Renderer* createRenderer() const override;
	};
}