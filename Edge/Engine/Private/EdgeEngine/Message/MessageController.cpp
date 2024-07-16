#include "MessageController.h"

#include "EdgeEngine/Core/UtilsMacros.h"

bool Edge::MessageController::init(const MessageProc& msgProc)
{
	m_msgProc = msgProc;

	return true;
}

void Edge::MessageController::release()
{
	m_msgProc = nullptr;
}

void Edge::MessageController::message(MessageType type, const char* message, const char* file, uint32_t line)
{
	EDGE_SAFE_CALL_ARGS(m_msgProc, type, message, file, line);
}
