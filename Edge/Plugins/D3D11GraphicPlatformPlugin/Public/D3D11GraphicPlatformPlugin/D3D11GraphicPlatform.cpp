#include "D3D11GraphicPlatform.h"

#include "D3D11GraphicDevice.h"
#include "TinySimCommon/Core/UtilsMacros.h"

#include <cassert>

bool TS_D3D11::D3D11GraphicPlatform::init()
{
	m_d3d11Device = new D3D11GraphicDevice();
	TS_CHECK_INITIALIZATION(m_d3d11Device);

	return true;
}

void TS_D3D11::D3D11GraphicPlatform::release()
{
	TS_SAFE_DESTROY(m_d3d11Device);
}

TS::GraphicDevice& TS_D3D11::D3D11GraphicPlatform::getGraphicDevice()
{
	assert(m_d3d11Device);
	return *m_d3d11Device;
}
