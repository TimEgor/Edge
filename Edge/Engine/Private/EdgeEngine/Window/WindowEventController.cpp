#include "WindowEventController.h"

#include "TinySimFramework/FrameworkCore.h"
#include "TinySimFramework/EventController/EventController.h"
#include "TinySimFramework/WindowController/Window.h"


void TS::WindowEventController::initWindowContextEvent()
{
	FrameworkCore::getInstance().getApplication().getEventController().registerEvent(WindowActivationEvent::getEventType());
}

void TS::WindowEventController::releaseWindowContextEvent()
{
	FrameworkCore::getInstance().getApplication().getEventController().unregisterEvent(WindowActivationEvent::getEventType());
}

void TS::WindowEventController::onWindowActivate(WindowHandleReference& window, bool isActive)
{
	const WindowActivationEvent windowEvent(window, isActive);
	FrameworkCore::getInstance().getApplication().getEventController().dispatchEvent(WindowActivationEvent::getEventType(), windowEvent);
}

void TS::WindowEventController::onWindowSizeChange(WindowHandleReference& window)
{
	const WindowSizeEvent windowEvent(window);
	FrameworkCore::getInstance().getApplication().getEventController().dispatchInstancedEvent(window->getWindow().getSizeEventID(), windowEvent);
}

TS::WindowEventController::WindowEventController()
{
	initWindowContextEvent();
}

TS::WindowEventController::~WindowEventController()
{
	releaseWindowContextEvent();
}
