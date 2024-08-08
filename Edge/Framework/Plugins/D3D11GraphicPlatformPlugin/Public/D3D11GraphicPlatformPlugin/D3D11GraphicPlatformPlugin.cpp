#include "D3D11GraphicPlatformPlugin.h"

#include "D3D11GraphicPlatform.h"

EDGE_MODULE_LOAD()
EDGE_PLUGIN(EdgeD3D11::D3D11GraphicPlatformPlugin, EDGE_PLUGIN_TYPE_DECLARATION_GRAPHIC_PLATFORM)

Edge::GraphicPlatform* EdgeD3D11::D3D11GraphicPlatformPlugin::createGraphicPlatform() const
{
	return new D3D11GraphicPlatform();
}
