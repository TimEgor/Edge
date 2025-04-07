#pragma once

#include "GraphicObject.h"

namespace Edge
{
	//Hack: SamplerState is a placeholder for a quick implementation and testing of the text rendering
	//TODO: add interface for setting

	class SamplerState : public GraphicObject
	{
	public:
		SamplerState() = default;
	};
}