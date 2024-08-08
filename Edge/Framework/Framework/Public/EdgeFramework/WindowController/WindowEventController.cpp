#include "WindowEventController.h"

#include "EdgeFramework/FrameworkCore.h"
#include "EdgeFramework/EventController/EventController.h"
#include "EdgeFramework/WindowController/Window.h"


void Edge::WindowEventController::initWindowContextEvent()
{
	FrameworkCore::getInstance().getApplication().getEventController().registerEvent(WindowActivationEvent::getEventType());
}

void Edge::WindowEventController::releaseWindowContextEvent()
{
	FrameworkCore::getInstance().getApplication().getEventController().unregisterEvent(WindowActivationEvent::getEventType());
}

void Edge::WindowEventController::onWindowActivate(WindowHandleReference& window, bool isActive)
{
	const WindowActivationEvent windowEvent(window, isActive);
	FrameworkCore::getInstance().getApplication().getEventController().dispatchEvent(WindowActivationEvent::getEventType(), windowEvent);
}

void Edge::WindowEventController::onWindowSizeChange(WindowHandleReference& window)
{
	const WindowSizeEvent windowEvent(window);
	FrameworkCore::getInstance().getApplication().getEventController().dispatchInstancedEvent(window->getWindow().getSizeEventID(), windowEvent);
}

Edge::WindowEventController::WindowEventController()
{
	initWindowContextEvent();
}

Edge::WindowEventController::~WindowEventController()
{
	releaseWindowContextEvent();
}
