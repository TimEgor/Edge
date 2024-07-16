#include "MTCountableObjectBase.h"

#include "EdgeEngine/Core/Multithreading/LockGuard.h"

#include <cassert>

Edge::MTCountableObjectBase::MTCountableObjectBase(size_t initialCounterVal)
	: m_counter(initialCounterVal), m_isAlive(true) {}

Edge::MTCountableObjectBase::~MTCountableObjectBase()
{
	assert(m_counter.load() == 0 && !m_isAlive);
}

bool Edge::MTCountableObjectBase::addReferenceCounter()
{
	LockGuard locker(m_lockState);

	if (m_isAlive)
	{
		incrementCounter();
		return true;
	}

	return false;
}

void Edge::MTCountableObjectBase::releaseReferenceObject()
{
	decrementCounter();
}

size_t Edge::MTCountableObjectBase::getReferenceCount() const
{
	return m_counter.load();
}

void Edge::MTCountableObjectBase::tryDestroy()
{
	UniqueLockGuard locker(m_lockState);

	if (m_counter.load() == 0 && m_isAlive)
	{
		m_isAlive = false;
		locker.unlock();

		selfDestroy();
	}
}

void Edge::MTCountableObjectBase::incrementCounter()
{
	m_counter.fetch_add(1);
}

void Edge::MTCountableObjectBase::decrementCounter()
{
	m_counter.fetch_add(-1);
	if (m_counter.load() == 0)
	{
		tryDestroy();
	}
}
