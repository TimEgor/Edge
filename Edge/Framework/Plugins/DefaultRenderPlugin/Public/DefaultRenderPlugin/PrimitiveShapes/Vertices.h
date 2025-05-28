#pragma once


#include "EdgeCommon/Math/Vector.h"

#include "EdgeFramework/Graphics/GraphicPlatform/GraphicObject/InputLayout.h"

namespace EdgeDefRender
{
	struct WireframeVertex final
	{
		Edge::FloatVector3 m_position = Edge::FloatVector3Zero;

		static const Edge::InputLayoutDesc::ElementDescContainer elementsDesc;
	};

	struct SolidVertex final
	{
		Edge::FloatVector3 m_position = Edge::FloatVector3Zero;
		Edge::FloatVector3 m_normal = Edge::FloatVector3Zero;
		Edge::FloatVector2 m_uv = Edge::FloatVector2Zero;

		static const Edge::InputLayoutDesc::ElementDescContainer elementsDesc;
	};
}