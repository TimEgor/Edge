#pragma once
#include "EdgeEngine/Message/IMessageController.h"

namespace Edge
{
	class MessageController final : public IMessageController
	{
	private:
		MessageProc m_msgProc = nullptr;

	public:
		MessageController() = default;

		virtual bool init(const MessageProc& msgProc) override;
		virtual void release() override;

		virtual void message(MessageType type, const char* message, const char* file, uint32_t line) override;
	};
}
