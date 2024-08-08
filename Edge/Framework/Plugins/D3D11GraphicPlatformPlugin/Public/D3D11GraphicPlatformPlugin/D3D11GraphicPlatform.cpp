#include "D3D11GraphicPlatform.h"

#include "EdgeCommon/UtilsMacros.h"

#include "D3D11GraphicDevice.h"

#include <cassert>

bool EdgeD3D11::D3D11GraphicPlatform::init()
{
	m_d3d11Device = new D3D11GraphicDevice();
	EDGE_CHECK_INITIALIZATION(m_d3d11Device);

	return true;
}

void EdgeD3D11::D3D11GraphicPlatform::release()
{
	EDGE_SAFE_DESTROY(m_d3d11Device);
}

Edge::GraphicDevice& EdgeD3D11::D3D11GraphicPlatform::getGraphicDevice()
{
	assert(m_d3d11Device);
	return *m_d3d11Device;
}
