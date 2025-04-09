#pragma once

#include "GraphicObject.h"

namespace Edge
{
	//Hack: DepthStencilState is a placeholder for a quick implementation and testing of the text rendering
	//TODO: add interface for setting

	class DepthStencilState : public GraphicObject
	{
	private:
		bool m_depthTestEnable = true;

	public:
		DepthStencilState(bool depthTestEnable)
			: m_depthTestEnable(depthTestEnable) {}

		bool isDepthTestEnable() const { return m_depthTestEnable; }
	};
}
