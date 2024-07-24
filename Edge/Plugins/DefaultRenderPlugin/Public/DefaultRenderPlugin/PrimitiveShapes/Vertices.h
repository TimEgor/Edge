#pragma once


#include "TinySimCommon/Math/Vector.h"

#include "TinySimFramework/Graphics/GraphicPlatform/GraphicObject/InputLayout.h"

namespace TS_DEF_RENDERER
{
	struct WireframeVertex final
	{
		TS::FloatVector3 m_position = TS::FloatVector3Zero;

		static const TS::InputLayoutDesc::ElementDescContainer elementsDesc;
	};

	struct SolidVertex final
	{
		TS::FloatVector3 m_position = TS::FloatVector3Zero;
		TS::FloatVector3 m_normal = TS::FloatVector3Zero;

		static const TS::InputLayoutDesc::ElementDescContainer elementsDesc;
	};
}