#pragma once

#include "EdgeFramework/Graphics/GraphicPlatform/GraphicPlatformPlugin.h"

namespace EdgeD3D11
{
	class D3D11GraphicPlatformPlugin final : public Edge::GraphicPlatformPlugin
	{
	public:
		D3D11GraphicPlatformPlugin(Edge::PluginModuleID moduleID)
			: GraphicPlatformPlugin(moduleID) {}

		virtual Edge::GraphicPlatform* createGraphicPlatform() const override;
	};
}