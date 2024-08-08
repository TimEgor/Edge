#include "Vertices.h"

const Edge::InputLayoutDesc::ElementDescContainer EdgeDefRender::WireframeVertex::elementsDesc = {
	{
		{"POSITION",0, 0, offsetof(WireframeVertex, m_position),
			3, Edge::InputLayoutElementType::Float32}
	}
};

const Edge::InputLayoutDesc::ElementDescContainer EdgeDefRender::SolidVertex::elementsDesc = {
	{
		{"POSITION",0, 0, offsetof(SolidVertex, m_position),
			3, Edge::InputLayoutElementType::Float32 },
		{"NORMAL",0, 0, offsetof(SolidVertex, m_normal),
			3, Edge::InputLayoutElementType::Float32 }
	}
};