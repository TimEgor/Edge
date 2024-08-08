#pragma once

#include "EdgeCommon/HashedType.h"

namespace Edge
{
	using EventType = HashedType::Type;
	constexpr EventType InvalidEventType = HashedType::InvalidType;

	class Event : public HashedType
	{
	public:
		Event() = default;
		virtual ~Event() = default;

		virtual EventType getType() const = 0;
	};

	using InstancedEventType = HashedType::Type;
	constexpr EventType InvalidInstancedEventType = HashedType::InvalidType;

	class InstancedEvent : public HashedType
	{
	public:
		InstancedEvent() = default;
		virtual ~InstancedEvent() = default;

		virtual InstancedEventType getType() const = 0;
	};
}

#define EDGE_EVENT_TYPE(EVENT_TYPE) EDGE_HASH_TYPE(#EVENT_TYPE, Edge::EventType, Event)
#define EDGE_INSTANCED_EVENT_TYPE(EVENT_TYPE) EDGE_HASH_TYPE(#EVENT_TYPE, Edge::InstancedEventType, InstancedEvents)
