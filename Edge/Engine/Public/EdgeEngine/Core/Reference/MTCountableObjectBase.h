#pragma once

#include "EdgeEngine/Core/Multithreading/SpinLock.h"

namespace Edge
{
	class MTCountableObjectBase
	{
	private:
		std::atomic<size_t> m_counter;
		mutable SpinLock m_lockState;
		bool m_isAlive;

		void tryDestroy();

	protected:
		virtual void selfDestroy() = 0;

		void incrementCounter();
		void decrementCounter();

	public:
		MTCountableObjectBase(size_t initialCounterVal = 0);
		virtual ~MTCountableObjectBase();

		bool addReferenceCounter();
		void releaseReferenceObject();

		size_t getReferenceCount() const;
	};

	class DefaultMTCountableObjectBase : public MTCountableObjectBase
	{
	private:
		virtual void selfDestroy() override;

	public:
		DefaultMTCountableObjectBase(size_t initialCounterVal = 0)
			: MTCountableObjectBase(initialCounterVal) {}
	};
}
