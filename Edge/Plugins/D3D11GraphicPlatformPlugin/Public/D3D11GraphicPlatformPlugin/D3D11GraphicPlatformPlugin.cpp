#include "D3D11GraphicPlatformPlugin.h"

#include "D3D11GraphicPlatform.h"

TS_MODULE_LOAD()
TS_PLUGIN(TS_D3D11::D3D11GraphicPlatformPlugin, TS_PLUGIN_TYPE_DECLARATION_GRAPHIC_PLATFORM)

TS::GraphicPlatform* TS_D3D11::D3D11GraphicPlatformPlugin::createGraphicPlatform() const
{
	return new D3D11GraphicPlatform();
}
