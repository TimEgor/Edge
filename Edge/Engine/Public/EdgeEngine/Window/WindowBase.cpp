#include "WindowBase.h"

#include "EdgeEngine/Core/UtilsMacros.h"
#include "EdgeEngine/EngineCore.h"
#include "EdgeEngine/Engine/IEngine.h"

#include "WindowEvents.h"

bool Edge::WindowBase::initWindowInstancedEvents()
{
	m_sizeEventID = GetEngine().getEventController().registerInstancedEvent(WindowSizeEvent::getInstancedEventsType());
	EDGE_CHECK_RETURN_FALSE(m_sizeEventID != InvalidInstancedEventID);

	return true;
}

void Edge::WindowBase::releaseWindowInstancedEvents()
{
	if (m_sizeEventID != InvalidInstancedEventID)
	{
		GetEngine().getEventController().unregisterInstancedEvent(m_sizeEventID);
		m_sizeEventID = InvalidInstancedEventID;
	}
}
