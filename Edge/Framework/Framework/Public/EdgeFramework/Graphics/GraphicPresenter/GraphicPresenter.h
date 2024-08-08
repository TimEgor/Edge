#pragma once

#include <cstdint>

namespace Edge
{
	class Texture2D;

	class GraphicPresenter
	{
	public:
		GraphicPresenter() = default;
		virtual ~GraphicPresenter() = default;

		virtual Texture2D* getTargetTexture() = 0;

		virtual void present() = 0;
	};
}