#pragma once

#include "TinySimFramework/Graphics/GraphicPlatform/GraphicPlatformPlugin.h"

namespace TS_D3D11
{
	class D3D11GraphicPlatformPlugin final : public TS::GraphicPlatformPlugin
	{
	public:
		D3D11GraphicPlatformPlugin(TS::PluginModuleID moduleID)
			: GraphicPlatformPlugin(moduleID) {}

		virtual TS::GraphicPlatform* createGraphicPlatform() const override;
	};
}