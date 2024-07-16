#pragma once

#include "EdgeEngine/Core/Patterns/NonCopyable.h"
#include "EdgeEngine/Message/IMessageController.h"

namespace Edge
{
	class IPluginController;
	class IWindowController;

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

		virtual IMessageController& getMessageController() const = 0;
		virtual IPluginController& getPluginController() const = 0;
		virtual IWindowController& getWindowController() const = 0;
	};
}
