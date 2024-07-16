#pragma once

#include <cstdint>

namespace Edge
{
	class IMessageController
	{
	public:
		enum class MessageType
		{
			Log,
			Warning,
			Error,

			Critical
		};

		using MessageProc = void(*)(MessageType type, const char* message, const char* file, uint32_t line);

		IMessageController() = default;
		virtual ~IMessageController() = default;

		virtual bool init(const MessageProc& msgProc) = 0;
		virtual void release() = 0;

		virtual void message(MessageType type, const char* message, const char* file, uint32_t line) = 0;
	};
}
