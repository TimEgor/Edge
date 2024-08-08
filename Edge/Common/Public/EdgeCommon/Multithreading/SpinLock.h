#pragma once

#include <atomic>

namespace Edge
{
	class SpinLock final
	{
	private:
		std::atomic_flag m_lockState = ATOMIC_FLAG_INIT;

	public:
		SpinLock() = default;

		void lock()
		{
			while (m_lockState.test_and_set()) {}
		}

		bool tryLock()
		{
			return !m_lockState.test_and_set();
		}

		void unlock()
		{
			m_lockState.clear();
		}

		bool try_lock() { return tryLock(); }
	};
}