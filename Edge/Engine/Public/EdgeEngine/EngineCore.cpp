#include "EngineCore.h"

#include "Core/UtilsMacros.h"
#include "EdgeEngine/Engine/Engine.h"

#include <cassert>

bool Edge::EngineCore::createEngine()
{
	if (!m_engine)
	{
		m_engine = new Engine();
		m_isEngineOwner = true;

		return true;
	}

	return false;
}

void Edge::EngineCore::destroyEngine()
{
	if (m_engine && m_isEngineOwner)
	{
		EDGE_SAFE_DESTROY(m_engine);
		m_isEngineOwner = false;
	}
}

Edge::IEngine& Edge::EngineCore::getEngine() const
{
	assert(m_engine);
	return *m_engine;
}

void Edge::EngineCore::setEngine(IEngine* engine)
{
	m_engine = engine;
}
