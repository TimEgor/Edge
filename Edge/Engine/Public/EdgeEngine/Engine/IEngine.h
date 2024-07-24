#pragma once

#include "EdgeEngine/Core/Patterns/NonCopyable.h"
#include "EdgeEngine/Message/IMessageController.h"

namespace Edge
{
	class IPluginController;
	class IEventController;

	class IPlatform;
	class IWindowController;

	class IGraphicPlatform;
	class IRenderController;

	class IEngine : public NonCopyable
	{
	public:
		struct InitData final
		{
			IMessageController::MessageProc m_messageProc;
		};

		IEngine() = default;
		virtual ~IEngine() = default;

		virtual bool init(const InitData& initData) = 0;
		virtual void release() = 0;

		virtual void run() = 0;
		virtual void stop() = 0;
		virtual void pause() = 0;
		virtual void unpause() = 0;

		virtual float getDeltaTime() const = 0;

		virtual bool isStopped() const = 0;
		virtual bool isPaused() const = 0;

		virtual IMessageController& getMessageController() const = 0;
		virtual IPluginController& getPluginController() const = 0;
		virtual IEventController& getEventController() const = 0;

		virtual IPlatform& getPlatform() const = 0;
		virtual IWindowController& getWindowController() const = 0;

		virtual IGraphicPlatform& getGraphicPlatform() const = 0;
		virtual IRenderController& getRenderController() const = 0;
	};
}
