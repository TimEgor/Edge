#pragma once

#include "EdgeEngine/EngineCore.h"
#include "EdgeEngine/Engine/IEngine.h"

#include "IMessageController.h"

#define EDGE_MESSAGE_LOG(msg)		\
	(void)(GetEngine().getMessageController().message(Edge::IMessageController::MessageType::Log, msg, __FILE__, uint32_t(__LINE__)))

#define EDGE_MESSAGE_WARNING(msg)	\
	(void)(GetEngine().getMessageController().message(Edge::IMessageController::MessageType::Warning, msg, __FILE__, uint32_t(__LINE__)))

#define EDGE_MESSAGE_ERROR(msg)		\
	(void)(GetEngine().getMessageController().message(Edge::IMessageController::MessageType::Error, msg, __FILE__, uint32_t(__LINE__)))

#define EDGE_MESSAGE_CRITICAL(msg)	\
	(void)(GetEngine().getMessageController().message(Edge::IMessageController::MessageType::Critical, msg, __FILE__, uint32_t(__LINE__)))