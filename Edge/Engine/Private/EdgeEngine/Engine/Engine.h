#pragma once

#include "EdgeEngine/Engine/IEngine.h"

namespace Edge
{
	class MessageController;
	class PluginController;

	class Engine final : public IEngine
	{
	private:
		MessageController* m_messageController = nullptr;
		PluginController* m_pluginController = nullptr;

		IWindowController* m_windowController = nullptr;

	public:
		Engine() = default;

		virtual bool init(const InitData& initData) override;
		virtual void release() override;

		virtual IMessageController& getMessageController() const override;
		virtual IPluginController& getPluginController() const override;
		virtual IWindowController& getWindowController() const override;
	};
}
