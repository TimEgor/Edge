#pragma once

#include "GraphicObject.h"

namespace Edge
{
	struct DepthStencilStateDesc final
	{
		bool m_depthTestEnable = true;
		bool m_depthWrite = true;
	};

	class DepthStencilState : public GraphicObject
	{
	private:
		DepthStencilStateDesc m_desc;

	public:
		DepthStencilState(const DepthStencilStateDesc& desc)
			: m_desc(desc) {}

		const DepthStencilStateDesc& getDesc() const { return m_desc; }
	};
}
