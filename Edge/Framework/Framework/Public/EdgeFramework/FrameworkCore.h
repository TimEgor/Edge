#pragma once

#include "Application/Application.h"
#include "EdgeCommon/Patterns/Singleton.h"

#include <cassert> 

namespace Edge
{
	class FrameworkCore final : public Singleton<FrameworkCore>
	{
	private:
		Application* m_application = nullptr;

	public:
		FrameworkCore() = default;

		Application& getApplication() const
		{
			assert(m_application);
			return *m_application;
		}

		void setApplication(Application* application) { m_application = application; } //Must be called before getApplication()
	};
}
