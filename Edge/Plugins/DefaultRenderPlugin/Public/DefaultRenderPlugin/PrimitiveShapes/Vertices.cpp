#include "Vertices.h"

const TS::InputLayoutDesc::ElementDescContainer TS_DEF_RENDERER::WireframeVertex::elementsDesc = {
	{
		{"POSITION",0, 0, offsetof(WireframeVertex, m_position),
			3, TS::InputLayoutElementType::Float32}
	}
};

const TS::InputLayoutDesc::ElementDescContainer TS_DEF_RENDERER::SolidVertex::elementsDesc = {
	{
		{"POSITION",0, 0, offsetof(SolidVertex, m_position),
			3, TS::InputLayoutElementType::Float32 },
		{"NORMAL",0, 0, offsetof(SolidVertex, m_normal),
			3, TS::InputLayoutElementType::Float32 }
	}
};