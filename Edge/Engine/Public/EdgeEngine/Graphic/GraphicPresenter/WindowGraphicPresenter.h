#pragma once

#include "EdgeEngine/Window/IWindow.h"

#include "IGraphicPresenter.h"

namespace Edge
{
	class Teture2D;
	class ISwapChain;

	struct SwapChainDesc;

	class WindowGraphicPresenter final : public IGraphicPresenter
	{
	private:
		ISwapChain* m_swapChain = nullptr;

	public:
		WindowGraphicPresenter() = default;
		~WindowGraphicPresenter() { release(); }

		bool init(const IWindow& window, const SwapChainDesc& swapChainDesc);
		void release();

		virtual ITexture2D* getTargetTexture() override;

		virtual void present() override;
	};
}
