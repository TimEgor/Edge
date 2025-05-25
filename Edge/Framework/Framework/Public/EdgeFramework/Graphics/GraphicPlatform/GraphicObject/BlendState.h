#pragma once

#include "GraphicObject.h"

namespace Edge
{
	//Hack: BlendState is a placeholder for a quick implementation and testing of the text rendering
	//TODO: add interface for setting

	enum class BlendMode
	{
		Off,
		AlphaBlend
	};

	class BlendState : public GraphicObject
	{
	private:
		BlendMode m_mode;

	public:
		BlendState(BlendMode mode)
			: m_mode(mode) {}

		BlendMode getMode() const { return m_mode; }
	};
}
