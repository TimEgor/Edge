#pragma once

#include "GraphicObject.h"

namespace Edge
{
	enum class RasterizationFillMode
	{
		Solid,
		Wireframe
	};

	enum class RasterizationCullMode
	{
		None,
		BackFace,
		FrontFace
	};

	struct RasterizationStateDesc final
	{
		RasterizationFillMode m_fillMode = RasterizationFillMode::Solid;
		RasterizationCullMode m_cullMode = RasterizationCullMode::None;
		bool m_frontCounterClockwise = false;
	};

	class RasterizationState : public GraphicObject
	{
	private:
		const RasterizationStateDesc m_desc;

	public:
		RasterizationState(const RasterizationStateDesc& desc)
			: m_desc(desc) {}

		const RasterizationStateDesc& getDesc() const { return m_desc; }
	};
}
