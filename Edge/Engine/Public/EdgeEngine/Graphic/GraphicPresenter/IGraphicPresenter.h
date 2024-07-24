#pragma once

#include <cstdint>

namespace Edge
{
	class ITexture2D;

	class IGraphicPresenter
	{
	public:
		IGraphicPresenter() = default;
		virtual ~IGraphicPresenter() = default;

		virtual ITexture2D* getTargetTexture() = 0;

		virtual void present() = 0;
	};
}