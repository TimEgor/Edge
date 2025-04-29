#pragma once

#include <atomic>

namespace Edge
{
	class MTCountableObjectBase
	{
	private:
		std::atomic<uint32_t> m_counter;

	protected:
		virtual void selfDestroy() = 0;

		void incrementCounter();
		void decrementCounter();

	public:
		MTCountableObjectBase(uint32_t initialCounterVal = 0);
		virtual ~MTCountableObjectBase();

		void addReferenceCounter();
		void releaseReferenceObject();

		uint32_t getReferenceCount() const;
	};

	class DefaultDestroyingMTCountableObjectBase : public MTCountableObjectBase
	{
	private:
		virtual void selfDestroy() override;

	public:
		DefaultDestroyingMTCountableObjectBase(uint32_t initialCounterVal = 0)
			: MTCountableObjectBase(initialCounterVal) {}
	};
}
