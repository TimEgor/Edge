#pragma once

#include "IGraphicObject.h"

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

	class IRasterizationState : public IGraphicObject
	{
	public:
		IRasterizationState() = default;

		virtual const RasterizationStateDesc& getDesc() const = 0;
	};

	class RasterizationStateBase : public IRasterizationState
	{
	private:
		const RasterizationStateDesc m_desc;

	public:
		RasterizationStateBase(const RasterizationStateDesc& desc)
			: m_desc(desc) {}

		virtual const RasterizationStateDesc& getDesc() const override { return m_desc; }
	};
}
