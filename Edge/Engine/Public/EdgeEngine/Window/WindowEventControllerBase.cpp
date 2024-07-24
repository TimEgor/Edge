#include "WindowEventControllerBase.h"

#include "EdgeEngine/EngineCore.h"
#include "EdgeEngine/Engine/IEngine.h"
#include "EdgeEngine/Event/EventController.h"


void Edge::WindowEventControllerBase::initWindowContextEvent()
{
	GetEngine().getEventController().registerEvent(WindowActivationEvent::getEventType());
}

void Edge::WindowEventControllerBase::releaseWindowContextEvent()
{
	GetEngine().getEventController().unregisterEvent(WindowActivationEvent::getEventType());
}

void Edge::WindowEventControllerBase::onWindowActivate(const WindowHandleReference& window, bool isActive)
{
	const WindowActivationEvent windowEvent(window, isActive);
	GetEngine().getEventController().dispatchInstancedEvent(WindowActivationEvent::getEventType(), windowEvent);
}

void Edge::WindowEventControllerBase::onWindowClose(const WindowHandleReference& window)
{
	const WindowClosingEvent windowEvent(window);
	GetEngine().getEventController().dispatchInstancedEvent(WindowActivationEvent::getEventType(), windowEvent);
}

void Edge::WindowEventControllerBase::onWindowSizeChange(const WindowHandleReference& window)
{
	const WindowSizeEvent windowEvent(window);
	GetEngine().getEventController().dispatchInstancedEvent(window->getWindow().getSizeEventID(), windowEvent);
}

Edge::WindowEventControllerBase::WindowEventControllerBase()
{
	initWindowContextEvent();
}

Edge::WindowEventControllerBase::~WindowEventControllerBase()
{
	releaseWindowContextEvent();
}
