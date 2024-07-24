#include "WindowGraphicPresenter.h"

#include "EdgeEngine/Core/UtilsMacros.h"
//#include "EdgeEngine/Core/Profile/Profile.h"

#include "EdgeEngine/EngineCore.h"
#include "EdgeEngine/Engine/IEngine.h"
#include "EdgeEngine/Graphics/GraphicPlatform/IGraphicDevice.h"
#include "EdgeEngine/Graphics/GraphicPlatform/IGraphicPlatform.h"
#include "EdgeEngine/Graphics/GraphicPlatform/GraphicObject/ISwapChain.h"

bool Edge::WindowGraphicPresenter::init(const IWindow& window, const SwapChainDesc& swapChainDesc)
{
	m_swapChain = GetEngine().getGraphicPlatform().getGraphicDevice().createSwapChain(swapChainDesc, window);
	EDGE_CHECK_RETURN_FALSE(m_swapChain);

	return true;
}

void Edge::WindowGraphicPresenter::release()
{
	EDGE_SAFE_DESTROY(m_swapChain);
}

Edge::ITexture2D* Edge::WindowGraphicPresenter::getTargetTexture()
{
	assert(m_swapChain);
	return m_swapChain->getTargetTexture();
}

void Edge::WindowGraphicPresenter::present()
{
	assert(m_swapChain);

	//EDGE_PROFILE_BLOCK_EVENT("Window swapchain presenting");
	m_swapChain->present();
}
