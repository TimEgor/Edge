#include "WindowGraphicPresenter.h"

#include "EdgeCommon/UtilsMacros.h"
#include "EdgeCommon/Profile/Profile.h"

#include "EdgeFramework/FrameworkCore.h"
#include "EdgeFramework/Graphics/GraphicPlatform/GraphicDevice.h"
#include "EdgeFramework/Graphics/GraphicPlatform/GraphicPlatform.h"
#include "EdgeFramework/Graphics/GraphicPlatform/GraphicObject/SwapChain.h"

bool Edge::WindowGraphicPresenter::init(const Window& window, const SwapChainDesc& swapChainDesc)
{
	m_swapChain = FrameworkCore::getInstance().getApplication().getGraphicPlatform().getGraphicDevice().createSwapChain(swapChainDesc, window);
	EDGE_CHECK_RETURN_FALSE(m_swapChain);

	return true;
}

void Edge::WindowGraphicPresenter::release()
{
	EDGE_SAFE_DESTROY(m_swapChain);
}

Edge::Texture2D* Edge::WindowGraphicPresenter::getTargetTexture()
{
	assert(m_swapChain);
	return m_swapChain->getTargetTexture();
}

void Edge::WindowGraphicPresenter::present()
{
	assert(m_swapChain);

	EDGE_PROFILE_BLOCK_EVENT("Window swapchain presenting");
	m_swapChain->present();
}
