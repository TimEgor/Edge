#pragma once

#include "EdgeFramework/WindowController/Window.h"

#include "GraphicPresenter.h"

namespace Edge
{
	class Teture2D;
	class SwapChain;

	struct SwapChainDesc;

	class WindowGraphicPresenter final : public GraphicPresenter
	{
	private:
		SwapChain* m_swapChain = nullptr;

	public:
		WindowGraphicPresenter() = default;
		~WindowGraphicPresenter() { release(); }

		bool init(const Window& window, const SwapChainDesc& swapChainDesc);
		void release();

		virtual Texture2D* getTargetTexture() override;

		virtual void present() override;
	};
}
