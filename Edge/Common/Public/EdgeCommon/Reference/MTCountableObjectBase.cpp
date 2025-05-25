#include "MTCountableObjectBase.h"

#include "EdgeCommon/Assert/AssertCore.h"
#include "EdgeCommon/Multithreading/LockGuard.h"

Edge::MTCountableObjectBase::MTCountableObjectBase(uint32_t initialCounterVal)
	: m_counter(initialCounterVal) {}

Edge::MTCountableObjectBase::~MTCountableObjectBase()
{
	EDGE_ASSERT(m_counter.load() == 0);
}

void Edge::MTCountableObjectBase::addReferenceCounter()
{
	incrementCounter();
}

void Edge::MTCountableObjectBase::releaseReferenceObject()
{
	decrementCounter();
}

uint32_t Edge::MTCountableObjectBase::getReferenceCount() const
{
	return m_counter.load();
}

void Edge::DefaultDestroyingMTCountableObjectBase::selfDestroy()
{
	delete this;
}

void Edge::MTCountableObjectBase::incrementCounter()
{
	m_counter.fetch_add(1);
}

void Edge::MTCountableObjectBase::decrementCounter()
{
	if (m_counter.fetch_add(-1) == 1)
	{
		selfDestroy();
	}
}
